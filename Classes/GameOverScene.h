//
//  GameOverScene.h
//  LittleDemon
//
//  Created by li bo on 14-1-6.
//
//

#ifndef __LittleDemon__GameOverScene__
#define __LittleDemon__GameOverScene__

#include <iostream>
#include "MainScene.h"

class GameOverScene:public MainScene{
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameOverScene, create);
    static CCScene* scene();
    void Retry();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName);
   
};

class GameOverSceneLayerLoader:public CCLayerLoader  {
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameOverSceneLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameOverScene);
};

#endif /* defined(__LittleDemon__GameOverScene__) */
