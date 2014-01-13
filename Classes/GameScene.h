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

enum {
    kTagBG,
    KTagBoard,
    kTagDemon
};

enum  {
    kDemonStanding,
    kDemonJumping,
    kDemonRising,
    kDemonFalling,
<<<<<<< HEAD
    kDemonLanding
=======
    kDemonDowning
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
};

enum  {
    kBoardNormal,
    kBoardPower,
    kBoardMorePower
    };

class GameScene:
public CCLayer,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener ,
public CCBSelectorResolver,
public CCBAnimationManagerDelegate
{
    
public:
    CCScene* scene();
    GameScene();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameScene, create);
    virtual ~GameScene();
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);
     virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char *pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual void completedAnimationSequenceNamed(const char *name);
    //节点加载
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    void pause(CCObject* pSender, CCControlEvent pCCControlEvent);
    void update(float dt);
    CCNode* LoadLayer(const char * pClassName, const char* pCCBFileName);

    CCNode* getCCbi(const char* name);
    void jump();
    CC_SYNTHESIZE(CCSize, _screenSize, ScreenSize) ;
    CC_SYNTHESIZE(CCScene*, mScene, mScene);
    void gameOver();
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);
    bool isLanding(CCNode* node);
    bool isMissing(CCNode* node);
    
private:
    CCArray* mBoardsArray;
    void ScrollBack(int delta);
    CCLabelTTF* mMyLabel;
<<<<<<< HEAD
    CCNode* mJump;
=======
    CCLabelTTF* mMyLabelHigh;
    CCNode* mDemonJump;
    CCNode* mDemonRise;
    CCNode* mDemonFall;
    CCNode* mDemonDown;
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
    CCNode* mGameLayer;
    CCSpriteFrameCache* mFrameCache;
    CCSprite* mBg1;
    CCSprite* mBg2;
    uint mHeightCurrent;
    uint mHeightRearch;
    uint mDemonState;
    uint mScore;
    CCBReader* mReader;
    CCBAnimationManager* mAManager1;
    CCBAnimationManager* mAManager2;
    CCBAnimationManager* mAManager3;
    CCBAnimationManager* mAManager4;
};

class GameSceneLayerLoader:public CCLayerLoader  {
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameSceneLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameScene);
  
};

#endif /* defined(__LittleDemon__GameScene__) */
