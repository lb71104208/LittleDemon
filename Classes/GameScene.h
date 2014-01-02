//
//  GameScene.h
//  LittleDemon
//
//  Created by libo on 14-1-2.
//
//

#ifndef __LittleDemon__GameScene__
#define __LittleDemon__GameScene__

#include <iostream>
#include "MainScene.h"

using namespace cocos2d;

class GameScene:
public CCLayer,
public CCBMemberVariableAssigner{
    
public:
    CCScene* scene();
    GameScene();
    virtual ~GameScene();
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);

    void update(float dt);
private:
    CCSprite* mBrickSprite;
};

#endif /* defined(__LittleDemon__GameScene__) */
