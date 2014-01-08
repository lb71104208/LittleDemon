//
//  GameScene.cpp
//  LittleDemon
//
//  Created by libo on 14-1-2.
//
//

#include "GameScene.h"
#include "GameOverScene.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define JUMP_HEIGHT 200
float offsetX = 0;

GameScene::GameScene():mBrickSprite(NULL),mMyLabel(NULL),mDemon(NULL),mGameLayer(NULL),mDemonState(kDemonStanding),mCurrentHeight(0)
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

CCNode* GameScene::getCCbi(const char* name)
{
    CCNodeLoaderLibrary* library = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    CCBReader* ccbReafer = new CCBReader(library);
    
    CCNode* node = ccbReafer->readNodeGraphFromFile(name);
    ccbReafer->autorelease();
    if(node != NULL)
    {
        return node;
    }
    return NULL;
    
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
    mDemon = this->getCCbi("jump1.ccbi");
    if(mDemon != NULL)
    {
        CCBAnimationManager* animationManager = (CCBAnimationManager*)mDemon->getUserObject();
        animationManager->runAnimationsForSequenceNamed("jump");
        mDemon->setPosition(200,200);
        this->addChild(mDemon);
    }
    setAccelerometerEnabled(true);
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this,0,false);
}

void GameScene::update(float delta)
{
    if (mBrickSprite!=NULL) {
        //mBrickSprite->setPosition(CCPoint(mBrickSprite->getPosition().x,mBrickSprite->getPosition().y-1));
    }
    
    switch (mDemonState) {
        case kDemonStanding:
            this->jump();
            break;
            
        case kDemonRising:
        {
            if (mCurrentHeight < JUMP_HEIGHT) {
                mDemon->setPosition(CCPoint(mDemon->getPositionX()+offsetX,mDemon->getPositionY()+5));
                mCurrentHeight+=5;
            }
            else{
                mDemonState = kDemonFalling;
            }
            break;
        }
            
        case kDemonFalling:
        {
            if (mDemon->getPositionY()<=0) {
                this->gameOver();
            }
            else if(isLanding(mDemon)==true)
            {
                mDemonState = kDemonStanding;
                mCurrentHeight = 0;
            }
            mDemon->setPosition(CCPoint(mDemon->getPositionX()+offsetX,mDemon->getPositionY()-5));
            break;
        }
            
        default:
            break;
    }
    
}

bool GameScene::isLanding(CCNode* node)
{
    if (mDemon->getPositionY()<=mBrickSprite->getPositionY()+30) {
        CCLog("%f, %f, %f",mDemon->getPositionX(),mBrickSprite->getPositionX()-mBrickSprite->getContentSize().width/2,mBrickSprite->getPositionX()+mBrickSprite->getContentSize().width/2);
        if (mDemon->getPositionX()>= mBrickSprite->getPositionX()-mBrickSprite->getContentSize().width/2
            &&mDemon->getPositionX()<= mBrickSprite->getPositionX()+mBrickSprite->getContentSize().width/2) {
            return true;
        }
    }
    return false;
}

void GameScene::didAccelerate(cocos2d::CCAcceleration *pAccelerationValue)
{
    offsetX = pAccelerationValue->x*10.0f;
    //mDemon->setPositionX(mDemon->getPositionX()+pAccelerationValue->x*20.0f);
}

void GameScene::jump()
{
    mCurrentHeight = 0;
    mDemonState = kDemonRising;
}

void GameScene::gameOver()
{
    CCDirector::sharedDirector()->replaceScene(GameOverScene::scene());
}

void GameScene::pause(CCObject* pSender, CCControlEvent pCCControlEvent)

{
    CCLog("paused!");
}