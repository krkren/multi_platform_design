// Classes updated in the multi-platform version
// Explains classes with added members using virtual code.

;----------------------------------------------------------------------------
;
;		System Related
;
;----------------------------------------------------------------------------
;----------------------------------------------------------------------------
;
;		*System Settings
;
;----------------------------------------------------------------------------
*SystemConfig
	;Save Related
	;[Save Enabled]
	;	Is saving enabled?
	;	Non-zero = Save enabled
	;[Auto-save Enabled]
	;	Is auto-saving enabled?
	;	Non-zero = Auto-save enabled
	;[Load Enabled]
	;	Is loading enabled?
	;	Non-zero = Load enabled
	;	(Used in trial versions, etc.)
	;
	;Message Related
	;[Message Speed]
	;	Message display speed
	;	Higher values are slower
	;[Message Skip]
	;	Message skip
	;	0 = Do not skip
	;	1 = Skip unread
	;	2 = Force skip
	;[Wait for Click]
	;	Wait for click
	;	0 = No
	;	1 = Yes
	;[Auto Message]
	;	Auto message
	;	0 = No
	;	1 = Yes
	;[Auto Message Speed]
	;	Auto message speed
	;	Higher values are slower
	;
	;Sound Related
	;[BGM Volume]
	;	BGM volume
	;	0-100
	;[SE Volume]
	;	SE volume
	;	0-100
	;[Voice Volume]
	;	Voice volume
	;	0-100
	;
	;Movie Related
	;[Movie Playback]
	;	Movie playback
	;	0 = No
	;	1 = Yes
	;
	;Miscellaneous
	;[Fullscreen]
	;	Fullscreen
	;	0 = Window
	;	1 = Fullscreen
	;[Text Decoration]
	;	Text decoration
	;	0 = No
	;	1 = Yes
	;[Blur Background]
	;	Blur background
	;	0 = Do not blur
	;	1 = Blur
	;[Use 3D Background]
	;	Use 3D background
	;	0 = Do not use
	;	1 = Use
	;
	;[Window Mode]		;Multi-platform
	;	Window mode
	;	0 = 16:9
	;	1 = 4:3
	;
	;[Language]			;Multi-platform
	;	Language
	;	0 = Japanese
	;	1 = English
	;	2 = Chinese (Simplified)
	;	3 = Chinese (Traditional)
	;	4 = Korean
	;
	;[Subtitle Display]			;Multi-platform
	;	Subtitle display
	;	0 = Do not display
	;	1 = Display
	;
	;[Subtitle Language]			;Multi-platform
	;	Subtitle language
	;	0 = Same as used language
	;	1 = Japanese
	;	2 = English
	;	3 = Chinese (Simplified)
	;	4 = Chinese (Traditional)
	;	5 = Korean
	;
	;[Voice Language]			;Multi-platform
	;	Voice language
	;	0 = Japanese
	;	1 = English
	;	2 = Korean
	;
	;[Region Settings]			;Multi-platform
	;	Region settings
	;	0 = Japan
	;	1 = North America
	;	2 = Korea
	;	3 = China
	;
	;[Age Rating]			;Multi-platform
	;	Age rating
	;	0 = Enabled
	;	1 = Disabled
	;
	;[Violence]			;Multi-platform
	;	Violence
	;	0 = Enabled
	;	1 = Disabled
	;
	;[Sexual Content]			;Multi-platform
	;	Sexual content
	;	0 = Enabled
	;	1 = Disabled
	;
	;[Use Controller]	;Multi-platform
	;	Use controller
	;	0 = Do not use
	;	1 = Use
	;
	;[Vibration]				;Multi-platform
	;	Vibration
	;	0 = No
	;	1 = Yes
	;
	;[Button Display]			;Multi-platform
	;	Button display
	;	0 = Do not display
	;	1 = Display
	;
	;[Message Window Display]	;Multi-platform
	;	Message window display
	;	0 = Do not display
	;	1 = Display
	;
	;[Skip Read]			;Multi-platform
	;	Skip read
	;	0 = Do not skip
	;	1 = Skip
	;
	;[Screen Effects]			;Multi-platform
	;	Screen effects
	;	0 = Enabled
	;	1 = Disabled