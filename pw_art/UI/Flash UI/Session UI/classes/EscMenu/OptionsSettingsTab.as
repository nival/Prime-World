package EscMenu 
{	
	import flash.text.TextField;
	import Components.ButtonStandart;
	import Components.PWCheckBox;
	import Components.PWCombobox;
	import Components.PWSlider;
	import flash.display.MovieClip;
	
	public class OptionsSettingsTab extends MovieClip
	{		
		public var video:TextField;
		public var graphicText:TextField;
		public var resolutionText:TextField;
		public var sound:TextField;
		public var music:TextField;
		public var sfx:TextField;
		public var voice:TextField;
		public var common:TextField;
		public var game:TextField;
		public var leftClick:TextField;
		public var windowMode:TextField;
		public var warning:TextField;
		public var useBadwordsFilterText:TextField;
		public var smartchat_cbText:TextField;
		
		public var apply_btn:ButtonStandart;
		public var cansel_btn:ButtonStandart;
		
		public var resolution:PWCombobox;
		public var graphic:PWCombobox;
		
		public var windowed_tb:PWCheckBox;
		public var leftClick_tb:PWCheckBox;
		public var useBadwordsFilter:PWCheckBox;
		public var smartchat_cb:PWCheckBox;
		
		public var sfx_mc:PWSlider;
		public var music_mc:PWSlider;
		public var voice_mc:PWSlider;		
		public var common_mc:PWSlider;
		
		public function AddedToStage():void
		{
			leftClick.x = leftClick.x - leftClick_tb.x;
			leftClick.y = leftClick.y - leftClick_tb.y;
			windowMode.x = windowMode.x - windowed_tb.x;
			windowMode.y = windowMode.y - windowed_tb.y;
			useBadwordsFilterText.x = useBadwordsFilterText.x - useBadwordsFilter.x;
			useBadwordsFilterText.y = useBadwordsFilterText.y - useBadwordsFilter.y;
			smartchat_cbText.x = smartchat_cbText.x - smartchat_cb.x;
			smartchat_cbText.y = smartchat_cbText.y - smartchat_cb.y;
			
			leftClick_tb.addChild(leftClick);
			windowed_tb.addChild(windowMode);
			useBadwordsFilter.addChild(useBadwordsFilterText);
			smartchat_cb.addChild(smartchat_cbText);
		}
		
		public function Localize():void
		{
			common.text = Localization.PreferenceMenu_CommonVolume;
			video.text = Localization.PreferenceMenu_GraphicLable;
			graphicText.text = Localization.PreferenceMenu_GraphicQualityLabel;
			resolutionText.text = Localization.PreferenceMenu_ResolutionLabel;
			sound.text = Localization.PreferenceMenu_SoundLabel;
			music.text = Localization.PreferenceMenu_MusicVolumeLabel;
			sfx.text = Localization.PreferenceMenu_SoundVolumeLabel;
			voice.text = Localization.PreferenceMenu_VoiceVolumeLabel;
			game.text = Localization.PreferenceMenu_GameLabel;
			leftClick.text = Localization.PreferenceMenu_LeftClickLabel;
			windowMode.text = Localization.PreferenceMenu_WindowModeLabel;
			warning.text = Localization.PreferenceMenu_Warning;
			apply_btn.LocalizeText = Localization.PreferenceMenu_AcceptBtn;
			cansel_btn.LocalizeText = Localization.PreferenceMenu_CancelBtn;
			useBadwordsFilterText.text = Localization.PreferenceMenu_UseBadWordsFilter;
			smartchat_cbText.text = Localization.PreferenceMenu_ReceiveRegularChatMessages;
		}
	}
}