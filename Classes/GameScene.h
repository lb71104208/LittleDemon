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
public CCBMemberVariableAssigner,
public CCNodeLoaderListener ,
public CCBSelectorResolver{
    
public:
    CCScene* scene();
    GameScene();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameScene, create);
    virtual ~GameScene();
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);
     virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char *pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    //节点加载
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    void pause(CCObject* pSender, CCControlEvent pCCControlEvent);
    void update(float dt);
    CCNode* LoadLayer(const char * pClassName, const char* pCCBFileName);
    
    CC_SYNTHESIZE(CCScene*, mScene, mScene);
private:
    CCSprite* mBrickSprite;
    CCLabelTTF* mMyLabel;
    CCNode* mDemonAnimation;
    CCNode* mGameLayer;
};

class GameSceneLayerLoader:public CCLayerLoader  {
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameSceneLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameScene);
};

#endif /* defined(__LittleDemon__GameScene__) */
