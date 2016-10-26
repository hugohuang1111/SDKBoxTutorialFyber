#include "HelloWorldScene.h"

#include "PluginFyber/PluginFyber.h"

USING_NS_CC;


class HelloWorldFyberListener : public sdkbox::FyberListener
{
public:
    virtual void onVirtualCurrencyConnectorFailed(int error,
                                                  const std::string& errorCode,
                                                  const std::string& errorMsg);
    virtual void onVirtualCurrencyConnectorSuccess(double deltaOfCoins,
                                                   const std::string& currencyId,
                                                   const std::string& currencyName,
                                                   const std::string& transactionId);
    
    //
    // Interstitial
    //
    
    virtual void onCanShowInterstitial(bool canShowInterstitial);
    virtual void onInterstitialDidShow();
    virtual void onInterstitialDismiss(const std::string& reason);
    virtual void onInterstitialFailed();
    
    //
    // Rewarded Video
    //
    
    virtual void onBrandEngageClientReceiveOffers(bool areOffersAvailable);
    virtual void onBrandEngageClientChangeStatus(int status, const std::string& msg);
    
    //
    // Offer Wall
    //
    
    virtual void onOfferWallFinish(int status);
};

void HelloWorldFyberListener::onVirtualCurrencyConnectorFailed(int error,
                                                               const std::string& errorCode,
                                                               const std::string& errorMsg) {
    CCLOG("onVirtualCurrencyConnectorFailed");
}

void HelloWorldFyberListener::onVirtualCurrencyConnectorSuccess(double deltaOfCoins,
                                                                const std::string& currencyId,
                                                                const std::string& currencyName,
                                                                const std::string& transactionId) {
    CCLOG("onVirtualCurrencyConnectorSuccess");
}

void HelloWorldFyberListener::onCanShowInterstitial(bool canShowInterstitial) {
    CCLOG("onCanShowInterstitial %s", canShowInterstitial ? "yes" : "no");
}

void HelloWorldFyberListener::onInterstitialDidShow() {
    CCLOG("onInterstitialDidShow");
}

void HelloWorldFyberListener::onInterstitialDismiss(const std::string& reason) {
    CCLOG("onInterstitialDismiss");
}

void HelloWorldFyberListener::onInterstitialFailed() {
    CCLOG("onInterstitialFailed");
}

void HelloWorldFyberListener::onBrandEngageClientReceiveOffers(bool areOffersAvailable) {
}

void HelloWorldFyberListener::onBrandEngageClientChangeStatus(int status, const std::string& msg) {
}

void HelloWorldFyberListener::onOfferWallFinish(int status) {
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
    
    auto label = Label::createWithTTF("Fyber Tutorials", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    addChild(label);

    MenuItemFont::setFontName("sans");
    MenuItemFont::setFontSize(20);
    Menu* menu = Menu::create(
                              MenuItemFont::create("requestInterstitial", [](Ref*) { sdkbox::PluginFyber::requestInterstitial(); }),
                              MenuItemFont::create("showOfferWall", [](Ref*) { sdkbox::PluginFyber::showOfferWall(); }),
                              MenuItemFont::create("request video", [](Ref*) { sdkbox::PluginFyber::requestOffers(); }),
                              MenuItemFont::create("request coins", [](Ref*) { sdkbox::PluginFyber::requestDeltaOfCoins(); }),
                              NULL);
    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(visibleSize.width/2, visibleSize.height/2);
    addChild(menu);

    _listener = new HelloWorldFyberListener();
    sdkbox::PluginFyber::setListener(_listener);
    sdkbox::PluginFyber::init();

    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
