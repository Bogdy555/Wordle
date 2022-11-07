#include "..\Headers\WordleAPI.hpp"



WordleAPI::Menu::Menu() : On(false), NextMenu(_NullMenu), QueuedMenu(_NullMenu), ApplicationObj(nullptr), PreviousMenuObj(nullptr)
{

}

WordleAPI::Menu::~Menu()
{

}

const uint64_t WordleAPI::Menu::GetMenuType() const
{
	return _NullMenu;
}

const bool WordleAPI::Menu::CheckOn() const
{
	return On;
}

const uint64_t WordleAPI::Menu::GetNextMenu() const
{
	return NextMenu;
}

const uint64_t WordleAPI::Menu::GetQueuedMenu() const
{
	return QueuedMenu;
}

WordleAPI::Application* WordleAPI::Menu::GetApplicationObj()
{
	return ApplicationObj;
}

const WordleAPI::Application* WordleAPI::Menu::GetApplicationObj() const
{
	return ApplicationObj;
}

WordleAPI::Menu* WordleAPI::Menu::GetPreviousMenuObj()
{
	return PreviousMenuObj;
}

const WordleAPI::Menu* WordleAPI::Menu::GetPreviousMenuObj() const
{
	return PreviousMenuObj;
}

WordleAPI::Time::Timer& WordleAPI::Menu::GetFrameTime(const size_t _Index)
{
	return ApplicationObj->GetFrameTime(_Index);
}

const WordleAPI::Time::Timer& WordleAPI::Menu::GetFrameTime(const size_t _Index) const
{
	return ApplicationObj->GetFrameTime(_Index);
}

const float WordleAPI::Menu::GetTimeStep() const
{
	return ApplicationObj->GetTimeStep();
}

const float WordleAPI::Menu::GetTimeStepRatio() const
{
	return ApplicationObj->GetTimeStepRatio();
}

const float WordleAPI::Menu::GetLagTime() const
{
	return ApplicationObj->GetLagTime();
}

const uint64_t WordleAPI::Menu::GetSync() const
{
	return ApplicationObj->GetSync();
}

void WordleAPI::Menu::TurnOn()
{
	On = true;
}

void WordleAPI::Menu::Close(const uint64_t _NextMenu)
{
	On = false;
	NextMenu = _NextMenu;
}

void WordleAPI::Menu::SetQueuedMenu(const uint64_t _QueuedMenu)
{
	QueuedMenu = _QueuedMenu;
}

void WordleAPI::Menu::BindApplication(Application* _ApplicationObj)
{
	ApplicationObj = _ApplicationObj;
}

void WordleAPI::Menu::UpdateCurrentFrameTime()
{
	ApplicationObj->UpdateCurrentFrameTime();
}

void WordleAPI::Menu::SetTimeStep(const float _TimeStep)
{
	ApplicationObj->SetTimeStep(_TimeStep);
}

void WordleAPI::Menu::SetLagTime(const float _LagTime)
{
	ApplicationObj->SetLagTime(_LagTime);
}

void WordleAPI::Menu::SetSync(const uint64_t _Sync)
{
	ApplicationObj->SetSync(_Sync);
}

void WordleAPI::Menu::Run(Application* _ApplicationObj)
{
	if (!_ApplicationObj)
	{
		return;
	}

	ApplicationObj = _ApplicationObj;

	PreviousMenuObj = ApplicationObj->GetCurrentMenuObj();

	ApplicationObj->SetCurrentMenuObj(this);

	Setup();
	while (On)
	{
		GetFrameTime(_Current).Start();

		Update();

		if (GetSync())
		{
			GetFrameTime(_Current).Stop();

			unsigned long _SleepTime = (unsigned long)((1.0f * Time::SecToMicro) / (float)(GetSync()) - GetFrameTime(_Current) * Time::SecToMicro);

			if ((long)(_SleepTime) > 0)
			{
				Time::SleepMicroSec(_SleepTime);
			}
		}

		GetFrameTime(_Current).Stop();

		GetFrameTime(_Previous) = GetFrameTime(_Current);

		if (QueuedMenu != _NullMenu)
		{
			QueuedMenus();
			QueuedMenu = _NullMenu;
		}

		if (!ApplicationObj->CheckOn())
		{
			Close(_NullMenu);
		}
	}
	Stop();

	ApplicationObj->SetCurrentMenuObj(PreviousMenuObj);
	ApplicationObj->SetCurrentMenu(NextMenu);

	ApplicationObj = nullptr;
	PreviousMenuObj = nullptr;
}
