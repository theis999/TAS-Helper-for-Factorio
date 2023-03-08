#include "TypePanel.h"

#include "cMain.h"
#include "utils.h"
#include "ParameterChoices.h"

using std::string;

/*
Type panel is the second panel at the top, with a radio button for each steptype
This file extends cMain.h to reduce the size of cMain.cpp
*/

void TypePanel::SwitchStep(STEP_TYPE::step_type type)
{
	cMain* parent = ((cMain*)this->GetParent());
	switch (type)
	{
		case STEP_TYPE::Take: parent->rbtn_take->SetValue(true);
			break;
		case STEP_TYPE::Put: parent->rbtn_put->SetValue(true);
			break;
		case STEP_TYPE::Game_Speed: parent->rbtn_game_speed->SetValue(true);
			break;
		case STEP_TYPE::Craft: parent->rbtn_craft->SetValue(true);
			break;
		case STEP_TYPE::Walk: parent->rbtn_walk->SetValue(true);
			break;
		case STEP_TYPE::Mine: parent->rbtn_mine->SetValue(true);
			break;
		case STEP_TYPE::Build: parent->rbtn_build->SetValue(true);
			break;
		case STEP_TYPE::Recipe: parent->rbtn_recipe->SetValue(true);
			break;
		case STEP_TYPE::Tech: parent->rbtn_tech->SetValue(true);
			break;
		case STEP_TYPE::Limit: parent->rbtn_limit->SetValue(true);
			break;
		case STEP_TYPE::Idle: parent->rbtn_idle->SetValue(true);
			break;
		case STEP_TYPE::Filter: parent->rbtn_filter->SetValue(true);
			break;
		case STEP_TYPE::Pause: parent->rbtn_pause->SetValue(true);
			break;
		case STEP_TYPE::Priority: parent->rbtn_priority->SetValue(true);
			break;
		case STEP_TYPE::Rotate: parent->rbtn_rotate->SetValue(true);
			break;
		case STEP_TYPE::Pick_Up: parent->rbtn_pick_up->SetValue(true);
			break;
		case STEP_TYPE::Drop: parent->rbtn_drop->SetValue(true);
			break;
		case STEP_TYPE::Launch: parent->rbtn_launch->SetValue(true);
			break;
		case STEP_TYPE::Save: parent->rbtn_save->SetValue(true);
			break;
		case STEP_TYPE::Stop: parent->rbtn_stop->SetValue(true);
			break;
		case STEP_TYPE::Cancel_Crafting: parent->rbtn_cancel_crafting->SetValue(true);
			break;
		default:
			// ERROR: You have done something wrong
			break;
	}
}

#pragma region cMain
void cMain::setup_paramters(const int parameters)
{
	using enum choice_bit_vector;
	spin_x->Enable(parameters & x_coordinate);
	spin_y->Enable(parameters & y_coordinate);
	spin_amount->Enable(parameters & amount);
	cmb_item->Enable(parameters & item);
	cmb_from_into->Enable(parameters & from_to);
	radio_input->Enable((bool)(input == (parameters & input)));
	radio_output->Enable((bool)(output == (parameters & output)));
	cmb_building_orientation->Enable(parameters & building_orientation);
	cmb_direction_to_build->Enable(parameters & direction_to_build);
	spin_building_size->Enable(parameters & building_size);
	spin_building_amount->Enable(parameters & amount_of_buildings);
}

// Finds the current radio button that is choosen, 
// determines which step type that is and returns the step name
string cMain::ExtractStep()
{
	//row 1
	if (rbtn_take->GetValue())
		return struct_steps_list.take;

	if (rbtn_put->GetValue())
		return struct_steps_list.put;

	if (rbtn_game_speed->GetValue())
		return struct_steps_list.game_speed;

	if (rbtn_craft->GetValue())
		return struct_steps_list.craft;

	if (rbtn_walk->GetValue())
		return struct_steps_list.walk;

	if (rbtn_mine->GetValue())
		return struct_steps_list.mine;

	if (rbtn_pause->GetValue())
		return struct_steps_list.pause;

	//row 2
	if (rbtn_build->GetValue())
		return struct_steps_list.build;

	if (rbtn_recipe->GetValue())
		return struct_steps_list.recipe;

	if (rbtn_tech->GetValue())
		return struct_steps_list.tech;

	if (rbtn_limit->GetValue())
		return struct_steps_list.limit;

	if (rbtn_idle->GetValue())
		return struct_steps_list.idle;

	if (rbtn_filter->GetValue())
		return struct_steps_list.filter;

	if (rbtn_stop->GetValue())
		return struct_steps_list.stop;

	//row 3
	if (rbtn_priority->GetValue())
		return struct_steps_list.priority;

	if (rbtn_rotate->GetValue())
		return struct_steps_list.rotate;

	if (rbtn_pick_up->GetValue())
		return struct_steps_list.pick_up;

	if (rbtn_drop->GetValue())
		return struct_steps_list.drop;

	if (rbtn_launch->GetValue())
		return struct_steps_list.launch;

	if (rbtn_save->GetValue())
		return struct_steps_list.save;

	if (rbtn_cancel_crafting->GetValue())
		return struct_steps_list.cancel_crafting;

	return "not found";
}
#pragma endregion

#pragma region cMain eventhandlers
void cMain::OnBuildChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.build);

	cmb_item->Clear();
	for (auto it = all_buildings.begin(); it < all_buildings.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_buildings.begin());
	cmb_item->AutoComplete(building_choices);

	label_item->SetLabelText(TypePanel::item);

	event.Skip();
}

void cMain::OnTakeChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.take);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	cmb_from_into->SetValue(TypePanel::output); // set default to output on take step

	label_item->SetLabelText(TypePanel::item);
	label_from_into->SetLabelText(TypePanel::from);

	event.Skip();
}

void cMain::OnPutChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.put);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	cmb_from_into->SetValue(TypePanel::input); // set default to input on put step

	label_item->SetLabelText(TypePanel::item);
	label_from_into->SetLabelText(TypePanel::into);

	event.Skip();
}

void cMain::OnCraftChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.craft);

	cmb_item->Clear();
	for (auto it = handcrafted_list.begin(); it < handcrafted_list.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*handcrafted_list.begin());
	cmb_item->AutoComplete(handcrafted_choices);

	label_item->SetLabelText(TypePanel::item);

	event.Skip();
}

void cMain::OnRotateChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.rotate);
	event.Skip();
}

void cMain::OnfilterChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.filter);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	label_item->SetLabelText(TypePanel::item);

	event.Skip();
}

void cMain::OnRecipeChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.recipe);

	cmb_item->Clear();
	for (auto it = all_recipes.begin(); it < all_recipes.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_recipes.begin());
	cmb_item->AutoComplete(recipe_choices);

	label_item->SetLabelText(TypePanel::recipe);

	event.Skip();
}

void cMain::OnTechChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.tech);

	cmb_item->Clear();
	for (auto it = tech_list.begin(); it < tech_list.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*tech_list.begin());
	cmb_item->AutoComplete(tech_choices);

	label_item->SetLabelText(TypePanel::tech);

	event.Skip();
}

void cMain::OnLaunchChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.launch);
	event.Skip();
}

void cMain::OnSaveChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.save);
	event.Skip();
}

void cMain::OnCancelCraftingChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.cancel_crafting);
	event.Skip();
}

void cMain::OnPriorityChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.priority);
	event.Skip();
}

void cMain::OnLimitChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.limit);
	event.Skip();
}

void cMain::OnIdleChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.idle);
	event.Skip();
}

void cMain::OnPickUpChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.pick);
	event.Skip();
}

void cMain::OnDropChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.drop);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	label_item->SetLabelText(TypePanel::item);

	event.Skip();
}

void cMain::OnPauseChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.Pause);
	event.Skip();
}

void cMain::OnStopChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.stop);
	event.Skip();
}

void cMain::OnWalkChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.walk);
	event.Skip();
}

void cMain::OnMineChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.mining);
	event.Skip();
}

void cMain::OnGameSpeedChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.game_speed);
	event.Skip();
}
#pragma endregion

#pragma region cMain Menu eventhandlers
void cMain::OnWalkMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Walk);
	OnWalkChosen(event);

	//// IMPORTANT -- This can be used to change the shortcuts of menuitems
	//wxAcceleratorEntry* plusAccel = new wxAcceleratorEntry(wxACCEL_CTRL, 50, wxID_ZOOM_IN);
	//menu_shortcuts->FindChildItem(10001)->SetAccel(plusAccel); // 10001 is the id of the menu item and can be set to what ever you want
	event.Skip();
}

void cMain::OnMineMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Mine);
	OnMineChosen(event);
	event.Skip();
}

void cMain::OnGameSpeedMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Game_Speed);
	OnGameSpeedChosen(event);
	event.Skip();
}

void cMain::OnBuildMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Build);
	OnBuildChosen(event);
	event.Skip();
}

void cMain::OnTakeMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Take);
	OnTakeChosen(event);
	event.Skip();
}

void cMain::OnPutMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Put);
	OnPutChosen(event);
	event.Skip();
}

void cMain::OnCraftMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Craft);
	OnCraftChosen(event);
	event.Skip();
}

void cMain::OnCancelCraftingMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Cancel_Crafting);
	OnCancelCraftingChosen(event);
	event.Skip();
}

void cMain::OnRecipeMenuChosen(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Recipe);
	OnRecipeChosen(event);
	event.Skip();
}

void cMain::OnRotateMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Rotate);
	OnRotateChosen(event);
	event.Skip();
}

void cMain::OnTechMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Tech);
	OnTechChosen(event);
	event.Skip();
}

void cMain::OnPriorityMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Priority);
	OnPriorityChosen(event);
	event.Skip();
}

void cMain::OnLimitMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Limit);
	OnLimitChosen(event);
	event.Skip();
}

void cMain::OnFilterMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Filter);
	OnfilterChosen(event);
	event.Skip();
}

void cMain::OnStopMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Stop);
	OnStopChosen(event);
	event.Skip();
}

void cMain::OnIdleMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Idle);
	OnIdleChosen(event);
	event.Skip();
}

void cMain::OnLaunchMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Launch);
	OnLaunchChosen(event);
	event.Skip();
}

void cMain::OnDropMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Drop);
	OnDropChosen(event);
	event.Skip();
}

void cMain::OnPickUpMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Pick_Up);
	OnPickUpChosen(event);
	event.Skip();
}

void cMain::OnSaveMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Save);
	OnSaveChosen(event);
	event.Skip();
}

void cMain::OnPauseMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(TypePanel::STEP_TYPE::Pause);
	OnPauseChosen(event);
	event.Skip();
}
#pragma endregion
