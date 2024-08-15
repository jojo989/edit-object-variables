#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class EditObjectPopup : public geode::Popup<> {
	protected:
		bool setup() override;
		float objectXpos;
		float objectYpos;
		float objectRotation;
		float objectScale;
		float objectID;
		CCMenuItemSpriteExtra* m_applyButton;
		void createInputs();
		void applyChanges(CCObject*);
		CCMenu* buttonMenu;
		geode::TextInput* xPosInput;
		geode::TextInput* yPosInput;
		geode::TextInput* rotationInput;
		geode::TextInput* scaleInput;
	public:	
		static EditObjectPopup* create();
		GameObject* selectedObject = GameManager::sharedState()->getEditorLayer()->m_editorUI->m_selectedObject;
};