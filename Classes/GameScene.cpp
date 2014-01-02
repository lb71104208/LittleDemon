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

GameScene::GameScene():mBrickSprite(NULL)
{
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(mBrickSprite);
}

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("GameScene", GameSceneLayerLoader::loader());
    CCBReader *reader = new CCBReader(lib);
    CCNode *  gameScene = reader->readNodeGraphFromFile("stage-single.ccbi");
    reader->autorelease();
    
    if (gameScene!=NULL)
    {
        scene->addChild(gameScene); //将node 添加到scene中
    }
    CCDirector::sharedDirector()->replaceScene(scene);
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this,0,false);
    return scene;
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
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBrickSprite", CCSprite *, this->mBrickSprite);
    return true;
}

bool GameScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

void GameScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLog("节点全部加载完毕");
}

void GameScene::update(float delta)
{
    if (mBrickSprite!=NULL) {
        mBrickSprite->setPosition(CCPoint(mBrickSprite->getPosition().x+1,mBrickSprite->getPosition().y));
    }
}

void GameScene::pause(CCObject* pSender, CCControlEvent pCCControlEvent)

{
    CCLog("paused!");
}