//
//  MainScene.cpp
//  LittleDemon
//
//  Created by li bo on 14-1-2.
//
//

#include "MainScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

MainScene::MainScene()
{
    
}

MainScene::~MainScene()
{
    
}

CCScene* MainScene::scene()
{
    CCScene *scene = CCScene::create();
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("MainScene", MainSceneLayerLoader::loader());
    CCBReader *reader = new CCBReader(lib);
    CCNode *  mainMenu = reader->readNodeGraphFromFile("mainmenu.ccbi");
    reader->release();
    if (mainMenu!=NULL)
    {
        scene->addChild(mainMenu); //将node 添加到scene中
    }
    
    return scene;
}

SEL_MenuHandler MainScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "single", MainScene::single);
    return NULL;
}

SEL_CCControlHandler MainScene::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "single", MainScene::single);
    return NULL;
}

void MainScene::single(cocos2d::CCObject *pSender, CCControlEvent pCCControlEvent)
{
    CCLog("Button Pressed!");
}

bool MainScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    
    return true;
}