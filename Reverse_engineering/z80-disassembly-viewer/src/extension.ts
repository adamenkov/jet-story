// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
import * as vscode from 'vscode';


function findDefinitionPosition(document: vscode.TextDocument, position: vscode.Position): vscode.Position | undefined {
	let word: string = document.getText(document.getWordRangeAtPosition(position));
	if ((word === '') || (word.length < 4)) {
		return undefined;
	}

	let text: string = document.getText(); 

	let definitionPosition: number = -1;
	if ((word.length === 5) && word.endsWith('h')) {
		word = word.substr(0, word.length - 1);
		definitionPosition = 1 + text.indexOf('\n' + word);
		if (definitionPosition === 0) {
			definitionPosition = -1;
		}
	}
	else {
		var regex = new RegExp('[0-9a-fA-F]{4} \.?' + word);
		definitionPosition = text.search(regex);
	}

	if (definitionPosition !== -1) {
		return document.positionAt(definitionPosition);
	}

	return undefined;
}


async function goTo() {
	let textEditor: vscode.TextEditor | undefined = vscode.window.activeTextEditor;
	if (!textEditor) {
		return;
	}
	
	let document: vscode.TextDocument = textEditor.document;
	let definitionPosition: vscode.Position | undefined = findDefinitionPosition(document, textEditor.selection.active);
	if (definitionPosition !== undefined) {
		textEditor.selection = new vscode.Selection(definitionPosition, definitionPosition);
		textEditor.revealRange(textEditor.selection, vscode.TextEditorRevealType.InCenterIfOutsideViewport);
	}
}


// this method is called when your extension is activated
// your extension is activated the very first time the command is executed
export function activate(context: vscode.ExtensionContext) {
	context.subscriptions.push(vscode.commands.registerCommand('extension.goTo', goTo));

	vscode.languages.registerHoverProvider({ pattern: '**/*.asm' }, {
		provideHover(document, position, token) {
			let definitionPosition: vscode.Position | undefined = findDefinitionPosition(document, position);
			if (definitionPosition !== undefined) {
				let hoverText: string = document.getText(new vscode.Range(definitionPosition.translate(-6), definitionPosition.translate(10)));
				if (hoverText !== '') {
					return { contents: [ '```\n' + hoverText + '```' ] };
				}
			}

			return undefined;
		}
	});

	vscode.window.onDidChangeTextEditorSelection(async (textEditorSelectionChangeEvent: vscode.TextEditorSelectionChangeEvent) => {
		let textEditor: vscode.TextEditor = textEditorSelectionChangeEvent.textEditor;
		if (!textEditor) {
			return;
		}
		
		let document: vscode.TextDocument = textEditor.document;
		if (!document.fileName.match(/\.asm$/)) {
			return;
		}

		let definitionPosition: vscode.Position | undefined = findDefinitionPosition(document, textEditor.selection.active);
		if (definitionPosition !== undefined) {
			let previewTextDocument: vscode.TextDocument = await vscode.workspace.openTextDocument({ content: document.getText() });
			let previewTextEditor: vscode.TextEditor = await vscode.window.showTextDocument(previewTextDocument, { 
				viewColumn: vscode.ViewColumn.Beside,
				preserveFocus: true,
				preview: true,
				selection: new vscode.Selection(definitionPosition, definitionPosition) });
			previewTextEditor.revealRange(previewTextEditor.selection, vscode.TextEditorRevealType.InCenterIfOutsideViewport);
		}
	});
}

// this method is called when your extension is deactivated
export function deactivate() {}
