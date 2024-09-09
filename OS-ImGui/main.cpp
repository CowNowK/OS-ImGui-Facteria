#define IMGUI_DEFINE_MATH_OPERATORS
#include <iostream>
#include "imgui/font.h"
#include "OS-ImGui.h"

DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;

namespace pic
{
	ID3D11ShaderResourceView* background = nullptr;

	ID3D11ShaderResourceView* aimbot = nullptr;
	ID3D11ShaderResourceView* visuals = nullptr;
	ID3D11ShaderResourceView* skins = nullptr;
	ID3D11ShaderResourceView* settings = nullptr;

	ID3D11ShaderResourceView* combo_widget = nullptr;
	ID3D11ShaderResourceView* input_widget = nullptr;

	ID3D11ShaderResourceView* menu_settings_icon = nullptr;

	ID3D11ShaderResourceView* circle_success = nullptr;
	ID3D11ShaderResourceView* circle_error = nullptr;

}

namespace font
{
	ImFont* inter_bold = nullptr;
	ImFont* inter_default = nullptr;
	ImFont* icon = nullptr;
}

void DrawCallBack()
{
	/*
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImFontConfig cfg;
	cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;
	
	font::inter_default = io.Fonts->AddFontFromMemoryTTF(inter_medium, sizeof(inter_medium), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	font::inter_bold = io.Fonts->AddFontFromMemoryTTF(inter_bold, sizeof(inter_bold), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	font::icon = io.Fonts->AddFontFromMemoryTTF(icon_font, sizeof(icon_font), 15.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	*/


	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(0, 0);
	style->WindowBorderSize = 0;
	style->ItemSpacing = ImVec2(20, 20);
	style->ScrollbarSize = 8.f;

	static float color[4] = { 0.f, 1.f, 0.f, 1.f };
	c::accent = { color[0], color[1], color[2], 1.f };

	ImGui::SetNextWindowSize(c::bg::size);
	ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus);
	{
		const ImVec2& pos = ImGui::GetWindowPos();
		const ImVec2& spacing = style->ItemSpacing;
		const ImVec2& region = ImGui::GetContentRegionMax();
		
		ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + region, ImGui::GetColorU32(c::bg::background), c::bg::rounding);
		ImGui::GetBackgroundDrawList()->AddRectFilled(pos + spacing, pos + ImVec2(180, 62 + +spacing.y), ImGui::GetColorU32(c::child::background), c::child::rounding);
		ImGui::GetBackgroundDrawList()->AddRect(pos + spacing, pos + ImVec2(180, 62 + spacing.y), ImGui::GetColorU32(c::child::outline), c::child::rounding);

		ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, 62 + spacing.y) + spacing, pos + ImVec2(180, region.y - spacing.y), ImGui::GetColorU32(c::child::background), c::child::rounding);
		ImGui::GetBackgroundDrawList()->AddRect(pos + ImVec2(0, 62 + spacing.y) + spacing, pos + ImVec2(180, region.y - spacing.y), ImGui::GetColorU32(c::child::outline), c::child::rounding);

		ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(180, 0) + spacing, pos + ImVec2(region.x - (spacing.x * 2) - 62, 62 + spacing.y), ImGui::GetColorU32(c::child::background), c::child::rounding);
		ImGui::GetBackgroundDrawList()->AddRect(pos + ImVec2(180, 0) + spacing, pos + ImVec2(region.x - (spacing.x * 2) - 62, 62 + spacing.y), ImGui::GetColorU32(c::child::outline), c::child::rounding);

		ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(region.x - (spacing.x * 2) - 62, 0) + spacing, pos + ImVec2(region.x - spacing.x, 62 + spacing.y), ImGui::GetColorU32(c::child::background), c::child::rounding);
		ImGui::GetBackgroundDrawList()->AddRect(pos + ImVec2(region.x - (spacing.x * 2) - 62, 0) + spacing, pos + ImVec2(region.x - spacing.x, 62 + spacing.y), ImGui::GetColorU32(c::child::outline), c::child::rounding);

		ImGui::GetWindowDrawList()->AddImage(pic::menu_settings_icon, pos + ImVec2(region.x - (spacing.x * 2) - 62, 0) + spacing + ImVec2(16, 16), pos + ImVec2(region.x - spacing.x, 62 + spacing.y) - ImVec2(16, 16), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(c::accent));

		ImGui::GlowText(font::inter_bold, 17.f, "AIMSTAR", pos + (ImVec2(180, 62 + spacing.y) + spacing - ImGui::CalcTextSize("AIMSTAR")) / 2, ImGui::GetColorU32(c::accent));

		static int tabs = 0, sub_tabs = 0;

		ImGui::SetCursorPos(ImVec2(spacing.x * 2, 62 + spacing.y * 3));
		ImGui::BeginGroup();
		{
			if (ImGui::Tabs(0 == tabs, pic::aimbot, "Visuals", ImVec2(180 - spacing.x * 3, 35), NULL)) tabs = 0;

			if (ImGui::Tabs(1 == tabs, pic::settings, "Misc", ImVec2(180 - spacing.x * 3, 35), NULL)) tabs = 1;

		}
		ImGui::EndGroup();

		ImGui::SetCursorPos(ImVec2(180 + spacing.x, spacing.y));
		ImGui::BeginGroup();
		{
			if (ImGui::SubTab(0 == sub_tabs, "ESP", ImVec2(80, 62))) sub_tabs = 0;
			ImGui::SameLine(0, 5);
			if (ImGui::SubTab(1 == sub_tabs, "Radar", ImVec2(80, 62))) sub_tabs = 1;
			ImGui::SameLine(0, 5);
			if (ImGui::SubTab(2 == sub_tabs, "Glow", ImVec2(80, 62))) sub_tabs = 2;
			ImGui::SameLine(0, 5);
			if (ImGui::SubTab(3 == sub_tabs, "Crosshairs", ImVec2(80, 62))) sub_tabs = 3;

		}
		ImGui::EndGroup();

		ImGui::SetCursorPos(ImVec2(180, 62 + spacing.y) + spacing);

		ImGui::BeginGroup();
		{
			ImGui::CustomBeginChild("GENERAL", ImVec2((region.x - (spacing.x * 3 + 180)) / 2, (region.y - (spacing.y * 4 + 62)) / 2.0f + 40));
			{

				static float color[4] = { 0.f, 1.f, 0.f, 1.f };
				static bool aimbot = true;
				ImGui::Pickerbox("Enabled Aimbot", &aimbot, color, picker_flags);

				static bool silent = false;
				static int key = 0, m = 0;
				ImGui::Keybindbox("Multibone", &silent, &key, &m);

				static int smooth = 7;
				ImGui::SliderInt("Smooth", &smooth, 0, 8);

				static float silent_fov = 5;
				ImGui::SliderFloat("FOV", &silent_fov, 0.f, 15.f, "%.2fF");
			}
			ImGui::CustomEndChild();

			ImGui::CustomBeginChild("MISC", ImVec2((region.x - (spacing.x * 3 + 180)) / 2, (region.y - (spacing.y * 4 + 62)) / 2.0f - 40));
			{

				static int select = 0;
				const char* items[10]{ "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };
				ImGui::Combo("Combo", &select, items, IM_ARRAYSIZE(items), 10);

				static bool multi_num[4] = { false, true, true, true};
				const char* multi_items[4] = { "One", "Two", "Three", "Four" };
				ImGui::MultiCombo("MultiCombo", multi_num, multi_items, 4);

			}
			ImGui::CustomEndChild();
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		{
			ImGui::CustomBeginChild("AIMBOT", ImVec2((region.x - (spacing.x * 3 + 180)) / 2, (region.y - (spacing.y * 4 + 62)) / 2.0f - 40));
			{

				static bool items[20];

				if (ImGui::BeginListBox("List Box", ImGui::GetContentRegionMax() - style->WindowPadding))
				{

					for (int i = 0; i != 20; i++) ImGui::Checkbox(std::to_string(i).c_str(), &items[i]);

					ImGui::EndListBox();
				}

			}
			ImGui::CustomEndChild();

			ImGui::CustomBeginChild("SETTINGS", ImVec2((region.x - (spacing.x * 3 + 180)) / 2, (region.y - (spacing.y * 4 + 62)) / 2.0f + 40));
			{
				static char input[64] = { "" };
				if (ImGui::InputTextEx("TextField", "Enter your text here", input, 64, ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40), NULL));
				ImGui::ColorEdit4("Color Picker", color, picker_flags);

				static int key = 0, m = 0;
				ImGui::Keybind("Keybind", &key, &m, true);
			}
			ImGui::CustomEndChild();
		}
		ImGui::EndGroup();


	}ImGui::End();

}

#ifdef OSIMGUI_INTERNAL

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		// Entry
		Gui.Start(hModule, DrawCallBack,OSImGui::DirectXType::AUTO);
	}
	return TRUE;
}

#endif

#ifndef OSIMGUI_INTERNAL

int main()
{
	try {
		//Gui.NewWindow("WindowName", Vec2(1000, 1000), DrawCallBack,false );
		Gui.AttachAnotherWindow("x64","", DrawCallBack);
	}
	catch (OSImGui::OSException& e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}

#endif