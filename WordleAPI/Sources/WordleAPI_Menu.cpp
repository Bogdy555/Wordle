#include "..\Headers\WordleAPI.hpp"



WordleAPI::Menu::Menu() : On(false), NextMenu(_NullMenu), ApplicationObj(nullptr)
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

WordleAPI::Application* WordleAPI::Menu::GetApplicationObj()
{
	return ApplicationObj;
}

const WordleAPI::Application* WordleAPI::Menu::GetApplicationObj() const
{
	return ApplicationObj;
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
	ApplicationObj->SetCurrentMenuObj(this);

	Setup();
	while (On)
	{
		GetFrameTime(_Current).Start();

		Update();

		if (GetSync())
		{
			GetFrameTime(_Current).Stop();

			float _ExpectedTime = Time::SecToMicro / (float)(GetSync());
			float _RealTime = GetFrameTime(_Current) * Time::SecToMicro;

			if (_RealTime < _ExpectedTime)
			{
				Time::SleepMicroSec((uint64_t)(_ExpectedTime) - (uint64_t)(_RealTime));
			}
		}

		GetFrameTime(_Current).Stop();

		GetFrameTime(_Previous) = GetFrameTime(_Current);

		if (!ApplicationObj->CheckOn())
		{
			Close(_NullMenu);
		}
	}
	Stop();

	ApplicationObj->SetCurrentMenu(NextMenu);
	ApplicationObj = nullptr;
}
