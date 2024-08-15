#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "editObjectPopup.hpp"
#include <Geode/modify/LevelEditorLayer.hpp>
class $modify(MyEditorUI, EditorUI) {	

	void createMoveMenu() {
		EditorUI::createMoveMenu();
		auto* btn = this->getSpriteButton("editSprite.png"_spr, menu_selector(MyEditorUI::onMyButton), nullptr, 0.9f);
		m_editButtonBar->m_buttonArray->addObject(btn);
		auto rows = GameManager::sharedState()->getIntGameVariable("0049");
		auto cols = GameManager::sharedState()->getIntGameVariable("0050");
		// TODO: replace with reloadItemsInNormalSize
		m_editButtonBar->reloadItems(rows, cols);
	}

	$override

	bool init(LevelEditorLayer* idk) {

		if (!EditorUI::init(idk)) {
			return false;
		}

		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());
		return true;
	}

	void onMyButton(CCObject*) {
		if (!m_selectedObject || m_selectedObjects->count() >= 2){
			FLAlertLayer::create("Error", "You can only edit 1 object lel", "Ok")->show();
			log::info("selObjects {}", m_selectedObjects->count());
			log::info("selectedObj {}", m_selectedObject);
			return;
		}
		EditObjectPopup::create()->show();
	}
};