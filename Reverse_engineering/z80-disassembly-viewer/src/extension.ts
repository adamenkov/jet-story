// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
import * as vscode from 'vscode';


function goTo() {
	let textEditor: vscode.TextEditor | undefined = vscode.window.activeTextEditor;
	if (!textEditor) {
		return;
	}
	
	let document: vscode.TextDocument = textEditor.document;
	let position: vscode.Position = textEditor.selection.active;
	let word: string = document.getText(document.getWordRangeAtPosition(position));
	if (word === '') {
		return;
	}

	let text: string = document.getText(); 

	let foundPosition: number = -1;
	if ((word.length === 5) && word.endsWith('h')) {
		word = word.substr(0, word.length - 1);
		foundPosition = 1 + text.indexOf('\n' + word);
	}
	else {
		var regex = new RegExp('[0-9a-fA-F]{4} \.?' + word);
		foundPosition = text.search(regex);
	}

	if (foundPosition !== -1) {
		let positionInDocument: vscode.Position = document.positionAt(foundPosition);
		textEditor.selection = new vscode.Selection(positionInDocument, positionInDocument);
		textEditor.revealRange(textEditor.selection, vscode.TextEditorRevealType.InCenterIfOutsideViewport);
	}
}


// this method is called when your extension is activated
// your extension is activated the very first time the command is executed
export function activate(context: vscode.ExtensionContext) {

	// Use the console to output diagnostic information (console.log) and errors (console.error)
	// This line of code will only be executed once when your extension is activated
		console.log('Congratulations, your extension "z80-disassembly-viewer" is now active!');

	// The command has been defined in the package.json file
	// Now provide the implementation of the command with registerCommand
	// The commandId parameter must match the command field in package.json
	let disposable = vscode.commands.registerCommand('extension.helloWorld', () => {
		// The code you place here will be executed every time your command is executed

		// Display a message box to the user
		vscode.window.showInformationMessage('Hello World!');
	});

	context.subscriptions.push(disposable);

	context.subscriptions.push(vscode.commands.registerCommand('extension.goTo', goTo));

	vscode.languages.registerHoverProvider({ pattern: '**/*.asm' }, {
		provideHover(document, position, token) {
			let word: string = document.getText(document.getWordRangeAtPosition(position));
			if (word === '') {
				return;
			}
		
			let text: string = document.getText(); 
		
			let foundPosition: number = -1;
			if ((word.length === 5) && word.endsWith('h')) {
				word = word.substr(0, word.length - 1);
				foundPosition = 1 + text.indexOf('\n' + word);
			}
			else {
				var regex = new RegExp('[0-9a-fA-F]{4} \.?' + word);
				foundPosition = text.search(regex);
			}
		
			if (foundPosition !== -1) {
				let positionInDocument: vscode.Position = document.positionAt(foundPosition);
				let hoverText : string = document.getText(new vscode.Range(positionInDocument.translate(-10), positionInDocument.translate(10)));
				if (hoverText !== '') {
					return { contents: [hoverText] };
				}
			}

			return undefined;
		}
	});
}

// this method is called when your extension is deactivated
export function deactivate() {}
