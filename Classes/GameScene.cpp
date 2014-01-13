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

#define GRAVITY 0.6

float offsetX = 0;
float speedX = 0;
float speedY = 0;
int highscore = 0;
int currentBoardTag = 0;

<<<<<<< HEAD
GameScene::GameScene():mBrickSprite(NULL),mMyLabel(NULL),mJump(NULL),mGameLayer(NULL),mReader(NULL),mDemonState(kDemonStanding),mCurrentHeight(0)
{
    
=======
GameScene::GameScene():mMyLabel(NULL),mDemonJump(NULL),mDemonRise(NULL),mDemonFall(NULL)
,mGameLayer(NULL),mFrameCache(NULL),mDemonDown(NULL), mScore(0),mHeightRearch(0)
,mReader(NULL),mDemonState(kDemonStanding),mBg1(NULL),mBg2(NULL),mHeightCurrent(NULL),
mAManager1(NULL),mAManager2(NULL),mAManager3(NULL),mAManager4(NULL),mMyLabelHigh(NULL)
{
    currentBoardTag = 0;
    mBoardsArray = CCArray::createWithCapacity(10);
    CC_SAFE_RETAIN(mBoardsArray);
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(mMyLabel);
    CC_SAFE_RELEASE(mGameLayer);
    CC_SAFE_RELEASE(mReader);
    CC_SAFE_RELEASE(mBg1);
    CC_SAFE_RELEASE(mBg2);
    CC_SAFE_RELEASE(mAManager1);
    CC_SAFE_RELEASE(mAManager2);
    CC_SAFE_RELEASE(mAManager3);
    CC_SAFE_RELEASE(mAManager4);
    CC_SAFE_RELEASE(mBoardsArray);
    CC_SAFE_RELEASE(mFrameCache);
    CC_SAFE_RELEASE(mMyLabelHigh);
     //CC_SAFE_RELEASE(mDemon);
}

CCScene* GameScene::scene()
{
    mScene = CCScene::create();
    //加载主layer
    mGameLayer = LoadLayer("GameScene", "stage-single.ccbi");
    if (mGameLayer!=NULL)
    {
        mScene->addChild(mGameLayer,1); //将node 添加到scene中
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
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBg1", CCSprite*, mBg1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTTF", CCLabelTTF *, mMyLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelHighTTF", CCLabelTTF*, mMyLabelHigh);
    return true;
}

bool GameScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

void GameScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    //加载背景2
    mBg2 = CCSprite::create("bg-sky.png");
    mBg2->setPosition(CCPoint( _screenSize.width/2,_screenSize.height+mBg2->getContentSize().height/2));
    this->addChild(mBg2,-1);
    
    //加载最高分
    highscore = CCUserDefault::sharedUserDefault()->getIntegerForKey("high");
    char buffer[32];
    sprintf(buffer, "%d",highscore);
    mMyLabelHigh -> setString(buffer);

    //加载跳板
    srand(time(0));
    mFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    mFrameCache->addSpriteFramesWithFile("board.plist");
    
    CCSprite* board;
    int y = 139;
    while (y<_screenSize.height) {
        board = CCSprite::createWithSpriteFrameName("board1.png");
        board->setTag(kBoardNormal);
        board->setPosition(CCPoint(rand()%(int)_screenSize.width,y));
        mBoardsArray->addObject(board);
        this->addChild(board);
        y = ((CCSprite*)mBoardsArray->lastObject())->getPositionY()+100+rand()%(300-100+1);
       
    }
    
    //加载角色动画layer
<<<<<<< HEAD
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
=======
    mDemonJump= this->getCCbi("1-1.ccbi");
    if(mDemonJump != NULL)
    {
        mAManager1 = (CCBAnimationManager*)mDemonJump->getUserObject();
        mAManager1->setDelegate(this);
        CC_SAFE_RETAIN(mAManager1);
        mAManager1->runAnimationsForSequenceNamedTweenDuration("jump", 0.8f);
        float x = ((CCSprite*)mBoardsArray->objectAtIndex(0))->getPositionX();
        float y = ((CCSprite*)mBoardsArray->objectAtIndex(0))->getPositionY()+30;
        
        mDemonJump->setPosition(CCPoint(x,y));
       
        this->addChild(mDemonJump);
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
    }
    
    mDemonRise= this->getCCbi("1-2.ccbi");
    if(mDemonRise != NULL)
    {
        mAManager2 = (CCBAnimationManager*)mDemonRise->getUserObject();
        CC_SAFE_RETAIN(mAManager2);
        //mAManager2->runAnimationsForSequenceNamed("rise");
        mAManager2->setDelegate(this);
        this->addChild(mDemonRise);
        mDemonRise->setVisible(false);
    }

    
    mDemonFall= this->getCCbi("1-3.ccbi");
    if(mDemonFall != NULL)
    {
        mAManager3 = (CCBAnimationManager*)mDemonFall->getUserObject();
        CC_SAFE_RETAIN(mAManager3);
 
        this->addChild(mDemonFall);
        mDemonFall->setVisible(false);
    }
    
    mDemonDown= this->getCCbi("1-4.ccbi");
    if(mDemonDown != NULL)
    {
        mAManager4 = (CCBAnimationManager*)mDemonDown->getUserObject();
        CC_SAFE_RETAIN(mAManager4);
        this->addChild(mDemonDown);
        mDemonDown->setVisible(false);
    }

    
    setTouchEnabled( true );
    setAccelerometerEnabled(true);
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this,0,false);
}

void GameScene::update(float delta)
{
    //ScrollBack();
    switch (mDemonState) {
        case kDemonStanding:
<<<<<<< HEAD
=======
            //this->jump();
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
            break;
            
        case kDemonRising:
        {
<<<<<<< HEAD
            if (mCurrentHeight < JUMP_HEIGHT) {
                mJump->setPosition(CCPoint(mJump->getPositionX()+offsetX,mJump->getPositionY()+speedY));
                mCurrentHeight+=speedY;
=======
            if (speedY>0) {
                if (mDemonRise->getPositionY()>700) {
                     mDemonRise->setPosition(CCPoint(mDemonRise->getPositionX()+speedX,mDemonRise->getPositionY()));
                    ScrollBack(speedY);
                }
                
                else
                {
                    mDemonRise->setPosition(CCPoint(mDemonRise->getPositionX()+speedX,mDemonRise->getPositionY()+speedY));
                }
                if (mDemonRise->getPositionX()<0) {
                    mDemonRise->setPositionX(_screenSize.width);
                }
                else if (mDemonRise->getPositionX()>_screenSize.width)
                {
                    mDemonRise->setPositionX(0);
                }
                
                mHeightCurrent+=speedY;
                
                if (mHeightCurrent > mHeightRearch) {
                    mHeightRearch = mHeightCurrent;
                    mScore = mHeightRearch;
                    char buffer[32];
                    sprintf(buffer, "%d",mScore);
                    mMyLabel-> setString(buffer);
                }
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
            }
            else{
                mDemonFall->setPosition(mDemonRise->getPosition());
                mDemonFall->setVisible(true);
                mDemonRise->setVisible(false);
                mAManager3->runAnimationsForSequenceNamed("fall");
                mDemonState = kDemonFalling;
            }
            
            speedY-=GRAVITY;
            break;
        }
            
        case kDemonFalling:
        {
<<<<<<< HEAD
            if (mJump->getPositionY()<=0) {
                this->gameOver();
            }
            else if(isLanding(mJump)==true)
=======
            if(isLanding(mDemonFall)==true)
            {
                mDemonJump->setPosition(mDemonFall->getPosition());
                mDemonJump->setVisible(true);
                mDemonFall->setVisible(false);
                mAManager1->runAnimationsForSequenceNamed("jump");
                mDemonState = kDemonStanding;
                break;
            }
            
            else if(isMissing(mDemonFall)==true)
            {
                mDemonDown->setPosition(mDemonFall->getPosition());
                mDemonDown->setVisible(true);
                mDemonFall->setVisible(false);
                mAManager4->runAnimationsForSequenceNamed("down");
                mDemonState = kDemonDowning;
                break;
            }
            
            mDemonFall->setPosition(CCPoint(mDemonFall->getPositionX()+speedX,mDemonFall->getPositionY()+speedY));
            mHeightCurrent+=speedY;
            if (mDemonFall->getPositionX()<0) {
                mDemonFall->setPositionX(_screenSize.width);
            }
            else if (mDemonFall->getPositionX()>_screenSize.width)
            {
                mDemonFall->setPositionX(0);
            }
            speedY-=GRAVITY;
            break;
        }
            
        case kDemonDowning:
        {
            if (mDemonDown->getPositionY()<=0) {
                if (mScore>highscore) {
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("high", mScore);
                    char buffer[32];
                    sprintf(buffer, "新高分：%d",mScore);
                    CCMessageBox(buffer,"打破纪录");
                }
                this->gameOver();
            }
            
            mDemonDown->setPosition(CCPoint(mDemonDown->getPositionX()+speedX,mDemonDown->getPositionY()+speedY));
            if (mDemonDown->getPositionX()<0) {
                mDemonDown->setPositionX(_screenSize.width);
            }
            else if (mDemonDown->getPositionX()>_screenSize.width)
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
            {
                mDemonDown->setPositionX(0);
            }
<<<<<<< HEAD
            mJump->setPosition(CCPoint(mJump->getPositionX()+offsetX,mJump->getPositionY()+speedY));
=======
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
            speedY-=GRAVITY;
            break;
        }
            
        default:
            break;
    }
    
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    mAManager2->runAnimationsForSequenceNamed("rise");
}

bool GameScene::isLanding(CCNode* node)
{
<<<<<<< HEAD
    if (mJump->getPositionY()<=mBrickSprite->getPositionY()+30) {
        CCLog("%f, %f, %f",mJump->getPositionX(),mBrickSprite->getPositionX()-mBrickSprite->getContentSize().width/2,mBrickSprite->getPositionX()+mBrickSprite->getContentSize().width/2);
        if (mJump->getPositionX()>= mBrickSprite->getPositionX()-mBrickSprite->getContentSize().width/2
            &&mJump->getPositionX()<= mBrickSprite->getPositionX()+mBrickSprite->getContentSize().width/2) {
            return true;
=======
    for (int i =mBoardsArray->count()-1; i>=0; i--) {
        CCSprite* board = (CCSprite*) mBoardsArray->objectAtIndex(i);
        if (node->getPositionY()<=board->getPositionY()+30&&node->getPositionY()>=board->getPositionY()-board->getContentSize().height/2) {
            if (node->getPositionX()>= board->getPositionX()-board->getContentSize().width/2
                &&node->getPositionX()<= board->getPositionX()+board->getContentSize().width/2) {
                currentBoardTag = board->getTag();
                return true;
            }
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
        }

    }
    
        return false;
}

bool GameScene::isMissing(CCNode* node)
{
    CCSprite* board = (CCSprite*) mBoardsArray->objectAtIndex(0);
    if (node->getPositionY()<board->getPositionY()) {
        return true;
    }
    else
        return false;
}

void GameScene::didAccelerate(cocos2d::CCAcceleration *pAccelerationValue)
{
        offsetX = pAccelerationValue->x*10;
        //mDemon->setPositionX(mDemon->getPositionX()+pAccelerationValue->x*20.0f);
        speedX = offsetX;
    
}

void GameScene::jump()
{
<<<<<<< HEAD
    mCurrentHeight = 0;
    if (mJump!=NULL) {
        speedY = 50.0f;
=======
    switch (currentBoardTag) {
        case kBoardNormal:
        {
            speedY = 20.0f;
            break;
        }
        
        case kBoardPower:
        {
            speedY = 40.0f;
            break;
        }
            
        case kBoardMorePower:
        {
            speedY = 60.0f;
            break;
        }
            
            
        default:
            break;
>>>>>>> 06e1cf36c9950946eaef312c25bb2f45afba6605
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

void GameScene::completedAnimationSequenceNamed(const char *name)
{
    if (strcmp(name, "jump") ==0) {
        mDemonRise->setPosition(mDemonJump->getPosition());
        mDemonRise->setVisible(true);
        mDemonJump->setVisible(false);
        if (mAManager2!=NULL) {
            mAManager2->runAnimationsForSequenceNamed("rise");
            this->jump();
        }
    }
}

void GameScene::ScrollBack(int delta)
{
    mBg1->setPosition(CCPoint(mBg1->getPosition().x,mBg1->getPosition().y-delta));
    mBg2->setPosition(CCPoint(mBg2->getPosition().x,mBg2->getPosition().y-delta));
    
    if (mBg1->getPositionY()<=-_screenSize.height/2) {
        mBg1->setPosition(CCPoint( _screenSize.width/2,_screenSize.height+mBg2->getPositionY()));
    }
    
    if (mBg2->getPositionY()<=-_screenSize.height/2) {
        mBg2->setPosition(CCPoint( _screenSize.width/2,_screenSize.height+mBg1->getPositionY()));
    }
    
    for (int i=0; i<mBoardsArray->count(); i++) {
        CCSprite* board = (CCSprite*)mBoardsArray->objectAtIndex(i);
        board->setPosition(CCPoint(board->getPosition().x,board->getPosition().y-delta));
        if (board->getPositionY()+board->getContentSize().height/2<0) {
            mBoardsArray->removeObject(board);
            this->removeChild(board);
            //生成新板砖
            int y = ((CCSprite*)mBoardsArray->lastObject())->getPositionY()+rand()%300/*rand()%125+1*/;
            while (y<_screenSize.height*1.5) {
                CCSprite* newboard = CCSprite::createWithSpriteFrameName("board1.png");
                newboard->setTag(kBoardNormal);
                for (int i = mBoardsArray->count()-1; i>=0; i--) {
                    if (((CCSprite*)mBoardsArray->objectAtIndex(i))->getTag() == kBoardNormal) {
                        y = ((CCSprite*)mBoardsArray->objectAtIndex(i))->getPositionY()+100+rand()%(300-100+1);
                        newboard->setPosition(CCPoint(rand()%(int)_screenSize.width,y));
                        mBoardsArray->addObject(newboard);
                        this->addChild(newboard);
                        break;
                    }
                }
            }
        }
    }
    
            //随机产生2倍、3倍道具
            CCSprite* bonusBoard;
            srand(mScore);
            int tag = rand()%1000;
            CCLog("%d",tag);
            if (tag<=5) {
                bonusBoard = CCSprite::createWithSpriteFrameName("board2.png");
                bonusBoard->setTag(kBoardPower);
                bonusBoard->setPosition(CCPoint(rand()%(int)_screenSize.width,rand()%(int)_screenSize.height));
                mBoardsArray->addObject(bonusBoard);
                this->addChild(bonusBoard);
            }
            else if (tag >=998)
            {
                bonusBoard = CCSprite::createWithSpriteFrameName("board3.png");
                bonusBoard->setTag(kBoardMorePower);
                bonusBoard->setPosition(CCPoint(rand()%(int)_screenSize.width,rand()%(int)_screenSize.height));
                mBoardsArray->addObject(bonusBoard);
                this->addChild(bonusBoard);
            }

}