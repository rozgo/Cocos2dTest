#include "HelloWorldScene.h"

USING_NS_CC;

const int MAGIC_SIZE = 120;

Node* MakeReel(uint length, Texture2D* source)
{
    auto node = Node::create();
    for (int i=0; i<length; ++i) {
        auto spriteIndex = rand() % 16;
        auto rect = Rect((spriteIndex % 4) * MAGIC_SIZE, floor(spriteIndex / 4.0) * MAGIC_SIZE, MAGIC_SIZE, MAGIC_SIZE);
        auto sprite = Sprite::createWithTexture(source, rect);
        sprite->setScale(0.45);
        sprite->setPosition(0, i * MAGIC_SIZE * 0.45);
        node->addChild(sprite);
    }
    return node;
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backdrop = Sprite::create("background.jpg");
    backdrop->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(backdrop, -10);
    
    auto clipNode = ClippingRectangleNode::create(Rect(-150, -100, 300, 200));
    clipNode->setPosition(visibleSize.width/2, visibleSize.height/2);
    
    auto clipDrop = Sprite::create("battle.png");
    clipNode->addChild(clipDrop);
    
    this->addChild(clipNode);
    
    auto battleFrame = Sprite::create("frame.png");
    battleFrame->setPosition(visibleSize.width/2, visibleSize.height/2);
    battleFrame->setScale(1.2);
    this->addChild(battleFrame);
    
    auto sheet = Sprite::create("pokemon.png");

    auto title = Sprite::createWithTexture(sheet->getTexture(), Rect(MAGIC_SIZE * 4,0,MAGIC_SIZE * 3,MAGIC_SIZE));
    title->setScale(0.8);
    title->setPosition(visibleSize.width/2, visibleSize.height - 20);
    this->addChild(title);
    
    for (int i=0; i < 5; ++i) {
        auto reel = MakeReel(100, sheet->getTexture());
        reel->setPosition(-110 + i * 55, -55);
        clipNode->addChild(reel);
        auto move = MoveTo::create(rand() % 3 + 5, Vec2(-110 + i * 55, -55 - 54 * 90));
        auto ease = EaseCubicActionInOut::create(move->clone());
        reel->runAction(ease);
    }
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
