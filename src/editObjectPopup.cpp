#include "EditObjectPopup.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;


void EditObjectPopup::applyChanges(CCObject* sender) {
    auto xPosStr = this->xPosInput->getString();
    auto scaleStr = this->scaleInput->getString();
    auto yPosStr = this->yPosInput->getString();
    auto rotationStr = this->rotationInput->getString();
    if (xPosStr != "" || scaleStr != "" || yPosStr != "" || rotationStr != "") {
        selectedObject->setPositionX(std::stof(xPosStr));
        selectedObject->setRScale(std::stof(scaleStr));
        selectedObject->setPositionY(std::stof(yPosStr));
        selectedObject->setRotation(std::stof(rotationStr));
    }
    else {
        FLAlertLayer::create("Error", "Some of the fields are empty lel.", "Ok")->show();
        return;
    }
}

void EditObjectPopup::createInputs() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto objectXpos = selectedObject->getPositionX();
    auto objectScale = selectedObject->getScale();
    auto objectYpos = selectedObject->getPositionY();
    auto objectRotation = selectedObject->getRotation();

    auto inputMenu = CCMenu::create();

    this->xPosInput = TextInput::create(100.f, "Object Xpos", "bigfont.fnt");
    this->xPosInput->setString(std::to_string(objectXpos));

    this->scaleInput = TextInput::create(100.f, "Object Scale", "bigfont.fnt");
    this->scaleInput->setString(std::to_string(objectScale));

    this->yPosInput = TextInput::create(100.f, "Object Ypos", "bigfont.fnt");
    this->yPosInput->setString(std::to_string(objectYpos));

    this->rotationInput = TextInput::create(100.f, "Object Rotation", "bigfont.fnt");
    this->rotationInput->setString(std::to_string(objectRotation));
    inputMenu->setContentSize({ 400.f, 100.f });
    
    xPosInput->setPositionX(-180.f);
    scaleInput->setPositionX(50.f);
    yPosInput->setPositionX(-65.f);
    rotationInput->setPositionX(180.f);
    inputMenu->setPosition(winSize / 2);
    inputMenu->addChild(xPosInput);
    inputMenu->addChild(scaleInput);
    inputMenu->addChild(yPosInput);
    inputMenu->addChild(rotationInput);
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

    auto xPosLabel = CCLabelBMFont::create("Object Xpos", "goldfont.fnt");
    xPosLabel->setPosition(105.f, winSize.height/2 + 25);
    xPosLabel->setScale(.9f);
    auto yPosLabel = CCLabelBMFont::create("Object Ypos", "goldfont.fnt");
    yPosLabel->setPosition(215.f, winSize.height / 2 + 25);
    yPosLabel->setScale(.9f);
    auto scaleLabel = CCLabelBMFont::create("Object Scale", "goldfont.fnt");
    scaleLabel->setPosition(340.f, winSize.height / 2 + 25);
    scaleLabel->setScale(.9f);
    auto rotationLabel = CCLabelBMFont::create("Object Rotation", "goldfont.fnt");
    rotationLabel->setPosition(460.f, winSize.height / 2 + 25);
    rotationLabel->setScale(.9f);
    this->addChild(xPosLabel);
    this->addChild(yPosLabel);
    this->addChild(scaleLabel);
    this->addChild(rotationLabel);
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