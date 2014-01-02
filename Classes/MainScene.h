//
//  MainScene.h
//  LittleDemon
//
//  Created by li bo on 14-1-2.
//
//

#ifndef __LittleDemon__MainScene__
#define __LittleDemon__MainScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
class MainScene:
public CCLayer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver
{
public:
    
    MainScene();
    ~MainScene();
    
    static CCScene* scene();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainScene, create);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char *pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    void single(CCObject* pSender, CCControlEvent pCCControlEvent);
    
};

class MainSceneLayerLoader:public CCLayerLoader  {
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainScene);
};

#endif /* defined(__LittleDemon__MainScene__) */
