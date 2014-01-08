//
//  GameOverScene.cpp
//  LittleDemon
//
//  Created by li bo on 14-1-6.
//
//

#include "GameOverScene.h"
#include "GameScene.h"

CCScene* GameOverScene::scene()
{
    CCScene *scene = CCScene::create();
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("GameOverScene", GameOverSceneLayerLoader::loader());
    CCBReader *reader = new CCBReader(lib);
    CCNode *  layer = reader->readNodeGraphFromFile("gameover-single.ccbi");
    reader->autorelease();
    if (layer!=NULL)
    {
        scene->addChild(layer); //将node 添加到scene中
    }
    
    return scene;
}

SEL_MenuHandler GameOverScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "retry", GameOverScene::Retry);
    return NULL;
}

void GameOverScene::Retry()
{
    GameScene* scene =  new GameScene();
    CCDirector::sharedDirector()->replaceScene(scene->scene());

}