//
//  GameScene.cpp
//  LittleDemon
//
//  Created by libo on 14-1-2.
//
//

#include "GameScene.h"
USING_NS_CC;
USING_NS_CC_EXT;

GameScene::GameScene():mBrickSprite(NULL),mMyLabel(NULL),mDemonAnimation(NULL),mGameLayer(NULL)
{
   
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(mBrickSprite);
    CC_SAFE_RELEASE(mMyLabel);
}

CCScene* GameScene::scene()
{
    mScene = CCScene::create();
    
    //加载主layer
    mGameLayer = LoadLayer("GameScene", "stage-single.ccbi");
    if (mGameLayer!=NULL)
    {
        mScene->addChild(mGameLayer); //将node 添加到scene中
    }
    
    return mScene;
}

CCNode* GameScene::LoadLayer(const char *pClassName, const char *pCCBFileName)
{
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader(pClassName, GameSceneLayerLoader::loader());
    CCBReader *reader = new CCBReader(lib);
    reader->autorelease();

    CCNode *  layer = reader->readNodeGraphFromFile(pCCBFileName);
 
    return layer;
}

SEL_MenuHandler GameScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pause", GameScene::pause);
    return NULL;
}

SEL_CCControlHandler GameScene::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

bool GameScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBrickSprite", CCSprite *, mBrickSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTTF", CCLabelTTF *, mMyLabel);

    return true;
}

bool GameScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

void GameScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    //加载角色动画layer
    mDemonAnimation = new CCNode(*LoadLayer("GameScene", "jump1.ccbi"));
    if (mDemonAnimation != NULL) {
         mDemonAnimation->setPosition(CCPoint(mBrickSprite->getPositionX(),mBrickSprite->getPositionY()+mDemonAnimation->getContentSize().height/2));
        //CCLog("%f %f",mScene->getPositionX(),mScene->getPositionY());
        this->addChild(mDemonAnimation);
    }
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this,0,false);
}

void GameScene::update(float delta)
{
    if (mBrickSprite!=NULL) {
        mBrickSprite->setPosition(CCPoint(mBrickSprite->getPosition().x,mBrickSprite->getPosition().y-1));
    }
    
    if (mDemonAnimation != NULL) {
        mDemonAnimation->setPosition(CCPoint(mBrickSprite->getPositionX(),mBrickSprite->getPositionY()+mDemonAnimation->getContentSize().height/2));
        //CCLog("%f %f",mScene->getPositionX(),mScene->getPositionY());
        //this->addChild(mDemonAnimation);
    }

    
}

void GameScene::pause(CCObject* pSender, CCControlEvent pCCControlEvent)

{
    CCLog("paused!");
}