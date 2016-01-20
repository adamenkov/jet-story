#ifndef __SESSION_H
#define __SESSION_H

#pragma once

#include "GameStates.h"


class Session : public GameState
{
public:
	virtual void OnEnter();
	virtual void Update();
	virtual void Render() const;
};


#endif	// #ifndef __SESSION_H
