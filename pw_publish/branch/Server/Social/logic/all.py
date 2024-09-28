#automatically generated file. do not modify it!!!

import os
__all__ = ["Check_nickname",
"Place_hero_to_building",
"Remove_hero_from_building",
"Start_building_production",
"Stop_building_production",
"Collect_production_results",
"Keepalive",
"Item_move_ts2ts",
"Item_move_ts2inv",
"Check_talent",
"Recalc_hero_forces",
"Item_move_inv2ts",
"Item_set_actbar_idx",
"Item_remove_new_status",
"Building_move",
"Building_place",
"Building_remove",
"Building_upgrade",
"Increase_building_lvl",
"Add_talent",
"Add_talent_ex",
"Add_all_talents",
"Add_all_talent_upgrade_entities",
"Remove_talents",
"Remove_all_talents",
"Give_fame",
"Reset_new_talents",
"Set_new_status",
"Give_experience",
"Give_rating",
"Increase_stat",
"Give_stat_points",
"Reset_stat_points",
"Give_resource",
"Hire_hero",
"Party_invite",
"Party_map",
"Party_accept",
"Party_decline",
"Party_disband",
"Party_kick",
"Party_hero",
"Party_go",
"Party_dodge",
"Party_status",
"Party_flag",
"Party_inventory_is_full",
"Clear_soulbound",
"Change_fraction",
"Ban_account",
"Mute_account",
"Expansion",
"Move_to_pocket",
"Move_from_pocket",
"Change_nickname",
"Purchase_guild_icon_change",
"Reset_counters",
"Clear_item_soulbound",
"Buy_cycle",
"Collect_talent",
"Add_ignore",
"Remove_ignore",
"Finish_production",
"Add_statistic",
"Add_quest",
"Try_complete_objective",
"Force_complete_objective",
"Complete_quest",
"Accept_quest",
"Skip_objective",
"Show_error",
"Add_friend_to_favorites",
"Remove_friend_from_favorites",
"Test_bool",
"Clear_mm",
"Buy_premium_account",
"Buy_premium_account_gm",
"Buy_unban_gm",
"Update_camera_flyby",
"Change_map",
"Change_pa_end",
"Change_last_login",
"Remove_friend",
"Uses_upg_herotal",
"Invite_friend",
"Accept_friend",
"Decline_friend",
"Search_friend",
"Add_friend",
"Return_friend",
"Add_fake_friends",
"Add_to_pocket",
"Mark_event_viewed",
"Buy_hero",
"Buy_hero_gold",
"Upgrade_hero",
"Merge_talents",
"Set_guard",
"Add_dodges",
"Unretire",
"Set_wins",
"Mm_ready",
"Upgrade_talent",
"Only_guard",
"Get_prices",
"Buy_special_hero",
"Check_pending_quests",
"Buy_skin",
"Select_skin",
"Clear_fwod",
"Refresh_ping_results",
"Guild_create",
"Guild_rename",
"Guild_leave",
"Guild_destroy",
"Guild_invite",
"Guild_accept",
"Guild_decline",
"Guild_promote",
"Guild_demote",
"Guild_change_owner",
"Guild_kick",
"Guild_invest_resources",
"Guild_msg",
"Guild_recalc",
"Guild_put_talent_to_bank",
"Guild_take_talent_from_bank",
"Guild_give_back",
"Guild_return_talent_to_bank",
"Guild_bank_limits_reset",
"Guild_buy_shop_item",
"Give_action",
"Set_last_payment",
"Tavern_reroll",
"Buy_steam_item",
"Confirm_steam_item",
"Set_steam_sex",
"Give_muid_dlc",
"Dlc_update",
"Dlc_register",
"Dlc_unregister",
"Test_ec",
"Buy_aeria_item",
"Buy_gamigo_item",
"Buy_arcgames_item",
"Buy_zzima_item",
"Billing_reserve_amount",
"Billing_confirm_writeoff",
"Billing_writeoff",
"Billing_replenish",
"Create_complaint",
"Reset_complaints",
"Set_lamp_last_roll",
"Buy_tournament_ticket",
"Update_tournament_info",
"Reset_tournament_account",
"Guild_delete_msg_recieved",
"Buy_custom_flag",
"Change_flag",
"Add_custom_flag",
"Set_md_version",
"Set_afk_state",
"Notify_tutorial_state_changed",
"Notify_session_ended",
"Accept_dynamic_quest",
"Force_complete_dynamic_objective",
"Try_complete_dynamic_objective",
"Complete_dynamic_quest",
"Reforge_talent",
"Reforge_upgrade_talent",
"Reset_dynamic_quests",
"Clear_dynamic_quests_from_server",
"Add_talent_quest",
"Craft_talents",
"Reset_last_played_time",
"Set_condition_reward_state",
"Give_decrease_rating_quest",
"Buy_beginners_pack",
"Get_guilddata_for_map",
"Guild_invite_suzerain",
"Start_siege",
"Leave_siege",
"Guild_accept_vassal",
"Guild_decline_vassal",
"Remove_vassal",
"Get_ex_vassals_list",
"Get_recommended_vassals_list",
"Get_guilds_list",
"Get_guild_requests_list",
"Set_guild_experience",
"Hide_recommended_vassal",
"Reset_sieges_counter",
"Remove_suzerain",
"Remove_npc_suzerain",
"Set_siege_duration",
"Add_vassal",
"Guild_shop_items_limits_reset",
"Set_siege_score",
"Remove_guild_buffs",
"Set_guild_buff_duration",
"Add_guild_buff",
"Set_guild_today_rating",
"Recalc_my_guild",
"Update_top_builds",
"Set_ex_vassal_left_time",
"Set_lost_target_left_time",
"Set_hero_last_played",
"Guild_set_recruitment_message",
"Guild_set_recruitment_locale",
"Guild_set_recruitment_rating",
"Guild_accept_recruit",
"Guild_decline_recruit",
"Create_recruit_application",
"Withdraw_recruit_application",
"Get_recommended_guilds_list",
"Guild_get_recruits_list",
"Remove_out_of_date_recruit_applications",
"Decrease_recruit_application_lifetime",
"Choose_party_again",
"Set_leaves",
"Remove_recent_ally",
"Reinit_recent_ally",
"Add_recent_ally",
"Context_resource_buy",
"Boost_buildingproduction",
"Set_boosted_production",
"Set_last_buy_value",
"Give_new_quest_from_pull",
"Guild_add_active_buff",
"Reset_punished_last_update_time",
"Moderator_mute_user",
"Reroll_shop",
"Reroll_shop_for_free",
"Buy_reroll_shop_item",
"Add_reroll_shop_item",
"Reroll_shop_with_statistics",
"Reset_reroll_shop",
"Remove_reroll_shop_group",
"Remove_reroll_shop_is_new_state",
"Remove_tal_upg_entities_is_new_state",
"Set_active_talentset",
"Set_talentset_message",
"Set_games",
"Set_playerrating",
"Change_friends_page",
"Get_legend_league_list",
"Set_season_results_showed",
"Update_hero_season_place",
"Roll_event_roll",
"Quest_event_choose",
"Dbg_quest_event_clear",
"Dbg_quest_event_choose",
"Trade_event_buy",
"Trade_event_give_reward",
"Dbg_trade_clear_remove",
"Season_event_buy_item",
"Season_event_give_reward",
"Dbg_season_clear_remove",
"Add_lootbox",
"Open_lootbox",
"Remove_lootbox",
"Upgrade_talent_by_entities",
"End_current_guild_war_event",
"Srv_debug",
]

from .check_nickname import *
from .place_hero_to_building import *
from .remove_hero_from_building import *
from .start_building_production import *
from .stop_building_production import *
from .collect_production_results import *
from .keepalive import *
from .item_move_ts2ts import *
from .item_move_ts2inv import *
from .check_talent import *
from .recalc_hero_forces import *
from .item_move_inv2ts import *
from .item_set_actbar_idx import *
from .item_remove_new_status import *
from .building_move import *
from .building_place import *
from .building_remove import *
from .building_upgrade import *
from .increase_building_lvl import *
from .add_talent import *
from .add_talent_ex import *
from .add_all_talents import *
from .add_all_talent_upgrade_entities import *
from .remove_talents import *
from .remove_all_talents import *
from .give_fame import *
from .reset_new_talents import *
from .set_new_status import *
from .give_experience import *
from .give_rating import *
from .increase_stat import *
from .give_stat_points import *
from .reset_stat_points import *
from .give_resource import *
from .hire_hero import *
from .party_invite import *
from .party_map import *
from .party_accept import *
from .party_decline import *
from .party_disband import *
from .party_kick import *
from .party_hero import *
from .party_go import *
from .party_dodge import *
from .party_status import *
from .party_flag import *
from .party_inventory_is_full import *
from .clear_soulbound import *
from .change_fraction import *
from .ban_account import *
from .mute_account import *
from .expansion import *
from .move_to_pocket import *
from .move_from_pocket import *
from .change_nickname import *
from .purchase_guild_icon_change import *
from .reset_counters import *
from .clear_item_soulbound import *
from .buy_cycle import *
from .collect_talent import *
from .add_ignore import *
from .remove_ignore import *
from .finish_production import *
from .add_statistic import *
from .add_quest import *
from .try_complete_objective import *
from .force_complete_objective import *
from .complete_quest import *
from .accept_quest import *
from .skip_objective import *
from .show_error import *
from .add_friend_to_favorites import *
from .remove_friend_from_favorites import *
from .test_bool import *
from .clear_mm import *
from .buy_premium_account import *
from .buy_premium_account_gm import *
from .buy_unban_gm import *
from .update_camera_flyby import *
from .change_map import *
from .change_pa_end import *
from .change_last_login import *
from .remove_friend import *
from .uses_upg_herotal import *
from .invite_friend import *
from .accept_friend import *
from .decline_friend import *
from .search_friend import *
from .add_friend import *
from .return_friend import *
from .add_fake_friends import *
from .add_to_pocket import *
from .mark_event_viewed import *
from .buy_hero import *
from .buy_hero_gold import *
from .upgrade_hero import *
from .merge_talents import *
from .set_guard import *
from .add_dodges import *
from .unretire import *
from .set_wins import *
from .mm_ready import *
from .upgrade_talent import *
from .only_guard import *
from .get_prices import *
from .buy_special_hero import *
from .check_pending_quests import *
from .buy_skin import *
from .select_skin import *
from .clear_fwod import *
from .refresh_ping_results import *
from .guild_create import *
from .guild_rename import *
from .guild_leave import *
from .guild_destroy import *
from .guild_invite import *
from .guild_accept import *
from .guild_decline import *
from .guild_promote import *
from .guild_demote import *
from .guild_change_owner import *
from .guild_kick import *
from .guild_invest_resources import *
from .guild_msg import *
from .guild_recalc import *
from .guild_put_talent_to_bank import *
from .guild_take_talent_from_bank import *
from .guild_give_back import *
from .guild_return_talent_to_bank import *
from .guild_bank_limits_reset import *
from .guild_buy_shop_item import *
from .give_action import *
from .set_last_payment import *
from .tavern_reroll import *
from .buy_steam_item import *
from .confirm_steam_item import *
from .set_steam_sex import *
from .give_muid_dlc import *
from .dlc_update import *
from .dlc_register import *
from .dlc_unregister import *
from .test_ec import *
from .buy_aeria_item import *
from .buy_gamigo_item import *
from .buy_arcgames_item import *
from .buy_zzima_item import *
from .billing_reserve_amount import *
from .billing_confirm_writeoff import *
from .billing_writeoff import *
from .billing_replenish import *
from .create_complaint import *
from .reset_complaints import *
from .set_lamp_last_roll import *
from .buy_tournament_ticket import *
from .update_tournament_info import *
from .reset_tournament_account import *
from .guild_delete_msg_recieved import *
from .buy_custom_flag import *
from .change_flag import *
from .add_custom_flag import *
from .set_md_version import *
from .set_afk_state import *
from .notify_tutorial_state_changed import *
from .notify_session_ended import *
from .accept_dynamic_quest import *
from .force_complete_dynamic_objective import *
from .try_complete_dynamic_objective import *
from .complete_dynamic_quest import *
from .reforge_talent import *
from .reforge_upgrade_talent import *
from .reset_dynamic_quests import *
from .clear_dynamic_quests_from_server import *
from .add_talent_quest import *
from .craft_talents import *
from .reset_last_played_time import *
from .set_condition_reward_state import *
from .give_decrease_rating_quest import *
from .buy_beginners_pack import *
from .get_guilddata_for_map import *
from .guild_invite_suzerain import *
from .start_siege import *
from .leave_siege import *
from .guild_accept_vassal import *
from .guild_decline_vassal import *
from .remove_vassal import *
from .get_ex_vassals_list import *
from .get_recommended_vassals_list import *
from .get_guilds_list import *
from .get_guild_requests_list import *
from .set_guild_experience import *
from .hide_recommended_vassal import *
from .reset_sieges_counter import *
from .remove_suzerain import *
from .remove_npc_suzerain import *
from .set_siege_duration import *
from .add_vassal import *
from .guild_shop_items_limits_reset import *
from .set_siege_score import *
from .remove_guild_buffs import *
from .set_guild_buff_duration import *
from .add_guild_buff import *
from .set_guild_today_rating import *
from .recalc_my_guild import *
from .update_top_builds import *
from .set_ex_vassal_left_time import *
from .set_lost_target_left_time import *
from .set_hero_last_played import *
from .guild_set_recruitment_message import *
from .guild_set_recruitment_locale import *
from .guild_set_recruitment_rating import *
from .guild_accept_recruit import *
from .guild_decline_recruit import *
from .create_recruit_application import *
from .withdraw_recruit_application import *
from .get_recommended_guilds_list import *
from .guild_get_recruits_list import *
from .remove_out_of_date_recruit_applications import *
from .decrease_recruit_application_lifetime import *
from .choose_party_again import *
from .set_leaves import *
from .remove_recent_ally import *
from .reinit_recent_ally import *
from .add_recent_ally import *
from .context_resource_buy import *
from .boost_buildingproduction import *
from .set_boosted_production import *
from .set_last_buy_value import *
from .give_new_quest_from_pull import *
from .guild_add_active_buff import *
from .reset_punished_last_update_time import *
from .moderator_mute_user import *
from .reroll_shop import *
from .reroll_shop_for_free import *
from .buy_reroll_shop_item import *
from .add_reroll_shop_item import *
from .reroll_shop_with_statistics import *
from .reset_reroll_shop import *
from .remove_reroll_shop_group import *
from .remove_reroll_shop_is_new_state import *
from .remove_tal_upg_entities_is_new_state import *
from .set_active_talentset import *
from .set_talentset_message import *
from .set_games import *
from .set_playerrating import *
from .change_friends_page import *
from .get_legend_league_list import *
from .set_season_results_showed import *
from .update_hero_season_place import *
from .roll_event_roll import *
from .quest_event_choose import *
from .dbg_quest_event_clear import *
from .dbg_quest_event_choose import *
from .trade_event_buy import *
from .trade_event_give_reward import *
from .dbg_trade_clear_remove import *
from .season_event_buy_item import *
from .season_event_give_reward import *
from .dbg_season_clear_remove import *
from .add_lootbox import *
from .open_lootbox import *
from .remove_lootbox import *
from .upgrade_talent_by_entities import *
from .end_current_guild_war_event import *
from .srv_debug import *
