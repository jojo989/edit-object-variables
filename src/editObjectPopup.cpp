#include "editObjectPopup.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

void EditObjectPopup::applyChanges(CCObject* sender) {
    auto xPosStr = this->xPosInput->getString();
    auto scaleXStr = this->scaleXInput->getString();
    auto scaleYStr = this->scaleYInput->getString();
    auto yPosStr = this->yPosInput->getString();
    auto rotationStr = this->rotationInput->getString();
    auto zOrderStr = this->zOrderInput->getString();
    if (xPosStr.empty() || scaleXStr.empty() || scaleYStr.empty() || yPosStr.empty() || rotationStr.empty() || zOrderStr.empty()) {
        FLAlertLayer::create("Error", "Some of the fields are empty lel.", "Ok")->show();
        return;
    }
    selectedObject->setPositionX(std::stof(xPosStr));
    selectedObject->setRScaleX(std::stof(scaleXStr));
    selectedObject->m_scaleX = stof(scaleXStr);
    selectedObject->setRScaleY(std::stof(scaleYStr));
    selectedObject->m_scaleY = stof(scaleYStr);
    selectedObject->setPositionY(std::stof(yPosStr));
    selectedObject->setRotation(std::stof(rotationStr));
    selectedObject->m_zOrder = stod(zOrderStr);
}

void EditObjectPopup::createInputs() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto objectXpos = selectedObject->getPositionX();
    auto objectScaleX = selectedObject->getScaleX();
    auto objectScaleY = selectedObject->getScaleY();
    auto objectYpos = selectedObject->getPositionY();
    auto objectRotation = selectedObject->getRotation();
    auto objectZorder = selectedObject->m_zOrder;

    auto inputMenu = CCMenu::create();

    this->xPosInput = TextInput::create(100.f, "Object Xpos", "bigfont.fnt");
    this->xPosInput->setString(std::to_string(objectXpos));

    this->yPosInput = TextInput::create(100.f, "Object Ypos", "bigfont.fnt");
    this->yPosInput->setString(std::to_string(objectYpos));

    this->scaleXInput = TextInput::create(100.f, "Object Scale X", "bigfont.fnt");
    this->scaleXInput->setString(std::to_string(objectScaleX));

    this->scaleYInput = TextInput::create(100.f, "Object Scale Y", "bigfont.fnt");
    this->scaleYInput->setString(std::to_string(objectScaleY));

    this->rotationInput = TextInput::create(100.f, "Object Rotation", "bigfont.fnt");
    this->rotationInput->setString(std::to_string(objectRotation));

    this->zOrderInput = TextInput::create(100.f, "Object Z Order", "bigfont.fnt");
    this->zOrderInput->setString(std::to_string(objectZorder));
    inputMenu->setContentSize({ 400.f, 100.f });
    
    xPosInput->setPositionX(-180.f);
    yPosInput->setPosition(-180.f, -64.f);
    scaleXInput->setPositionX(-65.f);
    scaleYInput->setPosition(-65.f, -64.f);
    rotationInput->setPosition(50.f, -32.f);
    zOrderInput->setPosition(165.f, -32.f);
    inputMenu->setPosition(winSize.width/2 ,(winSize.height/2) + 37);
    inputMenu->addChild(xPosInput);
    inputMenu->addChild(yPosInput);
    inputMenu->addChild(scaleXInput);
    inputMenu->addChild(scaleYInput);
    inputMenu->addChild(rotationInput);
    inputMenu->addChild(zOrderInput);
    this->addChild(inputMenu);
}


bool EditObjectPopup::setup() {
	m_noElasticity = true;
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	this->setTitle("Edit Object Variables");
    auto m_applyButton = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Apply changes"),
        this,
        menu_selector(EditObjectPopup::applyChanges)
    );
    auto buttonMenu = CCMenu::create();
    m_applyButton->setPositionY(-75);
    buttonMenu->setPosition(winSize/2);
    buttonMenu->addChild(m_applyButton);

    auto xPosLabel = CCLabelBMFont::create("Obj. Xpos", "goldfont.fnt");
    xPosLabel->setPosition(105.f, winSize.height / 2 + 62);
    xPosLabel->setScale(.75f);
    auto yPosLabel = CCLabelBMFont::create("Obj. Ypos", "goldfont.fnt");
    yPosLabel->setPosition(105.f, winSize.height / 2 );
    yPosLabel->setScale(.75f);
    auto scaleXLabel = CCLabelBMFont::create("Obj. Scale X", "goldfont.fnt");
    scaleXLabel->setPosition(225.f, winSize.height / 2 + 62);
    scaleXLabel->setScale(.75f);
    auto scaleYLabel = CCLabelBMFont::create("Obj. Scale Y", "goldfont.fnt");
    scaleYLabel->setPosition(225.f, winSize.height / 2);
    scaleYLabel->setScale(.75f);
    auto rotationLabel = CCLabelBMFont::create("Obj. Rotation", "goldfont.fnt");
    rotationLabel->setPosition(330.f, winSize.height / 2 + 32);
    rotationLabel->setScale(.75f);
    auto zOrderLabel = CCLabelBMFont::create("Obj. Z order", "goldfont.fnt");
    zOrderLabel->setPosition(445.f, winSize.height / 2 + 32);
    zOrderLabel->setScale(.75f);
    this->addChild(xPosLabel);
    this->addChild(yPosLabel);
    this->addChild(scaleXLabel);
    this->addChild(scaleYLabel);
    this->addChild(rotationLabel);
    this->addChild(zOrderLabel);
    this->addChild(buttonMenu);


    createInputs();

    return true;
}

EditObjectPopup* EditObjectPopup::create() {
    auto ret = new EditObjectPopup();
    if (ret && ret->init(485.f, 230.f)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
};