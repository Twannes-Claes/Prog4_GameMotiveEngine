#include "Player.h"

#include <SDL_keycode.h>

#include "AnimationTexture.h"
#include "CommandClasses.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "HealthComponent.h"
#include "LivesDisplay.h"
#include "Transform.h"

namespace Monke
{
	Player::Player(GameObject* pParent, const PlayerControlInfo& infoControls)
	:BaseComponent(pParent)
	{
		const int index = infoControls.playerIndex;
		const bool secondController = infoControls.secondController;
		const int gamemode = infoControls.gamemode;

		const auto pTexture = ResourceManager::Get().LoadTexture("Player/Player" + std::to_string(index) + "_Walk.png");

		GetOwner()->AddComponent<AnimationTexture>(pTexture, 4, 1, 4);
		GetOwner()->AddComponent<Rigidbody>(glm::vec2(48, 622), glm::vec2(48, 48), index, gamemode, secondController);
		const auto pHealthComp = GetOwner()->AddComponent<HealthComponent>(100.f, 3);

		const auto pLivesObj = GetOwner()->AddCreateChild();
		pLivesObj->SetParent(nullptr);

		pLivesObj->GetTransform()->SetPosition(0, 720);

		pLivesObj->AddComponent<LivesDisplay>(pHealthComp);

		if(index == 1)
		{
			InputManager::Get().AddCommand<MoveCommand>(SDLK_w, SDLK_d, SDLK_s, SDLK_a, std::make_unique<MoveCommand>(GetOwner(), 150.f));

			InputManager::Get().AddCommand<BubbleShootCommand>(SDLK_LSHIFT,InputManager::InputType::OnRelease , std::make_unique<BubbleShootCommand>(GetOwner(), pHealthComp));

			if(secondController || gamemode == 1)
			{
				InputManager::Get().AddCommand<MoveCommand>(0, Gamepad::GamepadButton::DPad_Up, Gamepad::GamepadButton::Dpad_Right, Gamepad::GamepadButton::DPad_Down, Gamepad::GamepadButton::DPad_Left, std::make_unique<MoveCommand>(GetOwner(), 150.f));
				InputManager::Get().AddCommand<BubbleShootCommand>(0, Gamepad::GamepadButton::Button_West, InputManager::InputType::OnRelease, std::make_unique<BubbleShootCommand>(GetOwner(), pHealthComp));
			}
		}
		else
		{
			pLivesObj->GetTransform()->SetPosition(650, 720);

			const unsigned int controllerIdx = secondController ? 1 : 0;

			InputManager::Get().AddCommand<MoveCommand>(controllerIdx, Gamepad::GamepadButton::DPad_Up, Gamepad::GamepadButton::Dpad_Right, Gamepad::GamepadButton::DPad_Down, Gamepad::GamepadButton::DPad_Left, std::make_unique<MoveCommand>(GetOwner(), 150.f));
			InputManager::Get().AddCommand<BubbleShootCommand>(controllerIdx, Gamepad::GamepadButton::Button_West, InputManager::InputType::OnRelease, std::make_unique<BubbleShootCommand>(GetOwner(), pHealthComp));
		}
	}
}


