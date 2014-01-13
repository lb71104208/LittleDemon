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
#define GRAVITY 3

float offsetX = 0;
float speedX = 0;
float speedY = 0;

GameScene::GameScene():mBrickSprite(NULL),mMyLabel(NULL),mJump(NULL),mGameLayer(NULL),mReader(NULL),mDemonState(kDemonStanding),mCurrentHeight(0)
{
    
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(mBrickSprite);
    CC_SAFE_RELEASE(mMyLabel);
    CC_SAFE_RELEASE(mGameLayer);
    CC_SAFE_RELEASE(mReader);
    //CC_SAFE_RELEASE(mDemon);
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
    mReader = new CCBReader(lib);
    mReader->autorelease();
    CCNode *  layer = mReader->readNodeGraphFromFile(pCCBFileName);
    
    return layer;
}

CCNode* GameScene::getCCbi(const char* name)
{
    CCNodeLoaderLibrary* library = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    CCBReader* ccbReader = new CCBReader(library);
    
    CCNode* node = ccbReader->readNodeGraphFromFile(name);
    ccbReader->autorelease();
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
    mJump = this->getCCbi("1-1.ccbi");
    if(mJump != NULL)
    {
        CCBAnimationManager* animationManager = (CCBAnimationManager*)mJump->getUserObject();
        animationManager->runAnimationsForSequenceNamed("Default Timeline");
        mJump->setPosition(200,200);
        speedX = 0;
        speedY = 0;
        this->addChild(mJump);
       setAccelerometerEnabled(true);
        setTouchEnabled( true );
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this,0,false);
    }
}

void GameScene::update(float delta)
{
    if (mBrickSprite!=NULL) {
        //mBrickSprite->setPosition(CCPoint(mBrickSprite->getPosition().x,mBrickSprite->getPosition().y-1));
    }
    
    switch (mDemonState) {
        case kDemonStanding:
            break;
            
        case kDemonRising:
        {
            if (mCurrentHeight < JUMP_HEIGHT) {
                mJump->setPosition(CCPoint(mJump->getPositionX()+offsetX,mJump->getPositionY()+speedY));
                mCurrentHeight+=speedY;
            }
            else{
                mDemonState = kDemonFalling;
            }
            
            speedY-=GRAVITY;
            break;
        }
            
        case kDemonFalling:
        {
            if (mJump->getPositionY()<=0) {
                this->gameOver();
            }
            else if(isLanding(mJump)==true)
            {
                mDemonState = kDemonStanding;
                mCurrentHeight = 0;
            }
            mJump->setPosition(CCPoint(mJump->getPositionX()+offsetX,mJump->getPositionY()+speedY));
            speedY-=GRAVITY;
            break;
        }
            
        default:
            break;
    
    }
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    this->jump();
}

bool GameScene::isLanding(CCNode* node)
{
    if (mJump->getPositionY()<=mBrickSprite->getPositionY()+30) {
        CCLog("%f, %f, %f",mJump->getPositionX(),mBrickSprite->getPositionX()-mBrickSprite->getContentSize().width/2,mBrickSprite->getPositionX()+mBrickSprite->getContentSize().width/2);
        if (mJump->getPositionX()>= mBrickSprite->getPositionX()-mBrickSprite->getContentSize().width/2
            &&mJump->getPositionX()<= mBrickSprite->getPositionX()+mBrickSprite->getContentSize().width/2) {
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
    if (mJump!=NULL) {
        speedY = 50.0f;
    }
   
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