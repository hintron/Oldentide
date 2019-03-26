// Filename:    main.go
// Author:      Joseph DeVictoria
// Date:        Mar_7_2019
// Description: Attempt to make Oldentide in a lower level engine.
//              Ack. Daniel Salvadori for bulk of base code.

package main

import (
	"github.com/g3n/engine/audio"
	"github.com/g3n/engine/audio/al"
	"github.com/g3n/engine/audio/vorbis"
	"github.com/g3n/engine/camera"
	"github.com/g3n/engine/camera/control"
	"github.com/g3n/engine/core"
	"github.com/g3n/engine/gls"
	"github.com/g3n/engine/graphic"
	"github.com/g3n/engine/gui"
	"github.com/g3n/engine/light"
	_ "github.com/g3n/engine/loader/obj"
	_ "github.com/g3n/engine/material"
	"github.com/g3n/engine/math32"
	"github.com/g3n/engine/renderer"
	"github.com/g3n/engine/text"
	"github.com/g3n/engine/util/logger"
	"github.com/g3n/engine/window"

	"flag"
	"fmt"
	_ "io/ioutil"
	"net/http"
	"net/url"
	"os"
	"path/filepath"
	"runtime"
	_ "strconv"
	"strings"
	"time"
)

var log *logger.Logger

// Client Game State Unique States
const (
	LOGIN_SCREEN                uint8 = iota
	CHARACTER_SELECT            uint8 = iota
	CHARACTER_CREATION_PHYSICAL uint8 = iota
	CHARACTER_CREATION_POINTS   uint8 = iota
	CHARACTER_CREATION_FINAL    uint8 = iota
	LOADING                     uint8 = iota
	IN_WORLD                    uint8 = iota
)

type OldentideClientGamestate struct {
	// g3n window and engine components
	wmgr              window.IWindowManager
	win               window.IWindow
	gs                *gls.GLS
	renderer          *renderer.Renderer
	scene             *core.Node
	camera            *camera.Perspective
	last_camera_angle *math32.Vector3
	orbit_control     *control.OrbitControl
	stepDelta         *math32.Vector2
	levelScene        *core.Node

	// Sound & Music players
	loginMusicPlayer *audio.Player

	// Fonts
	font *text.Font

	// Gui components
	root                        *gui.Root
	login_menu                  *gui.Panel
	login_username              *gui.Edit
	login_password_edit         *gui.Edit
	login_server_address        *gui.Edit
	login_server_web_port       *gui.Edit
	login_server_game_port      *gui.Edit
	login_login_button          *gui.Button
	login_quit_button           *gui.Button
	login_process               *gui.Panel
	login_process_slider        *gui.Slider
	login_process_status        *gui.Label
	cs_menu                     *gui.Panel
	cs_characters               *gui.List
	cs_enter_world_button       *gui.Button
	cs_create_character_button  *gui.Button
	cs_back_button              *gui.Button
	cs_quit_button              *gui.Button
	cc_physical_menu            *gui.Panel
	cc_physical_first_name      *gui.Edit
	cc_physical_last_name       *gui.Edit
	cc_physical_model_panel     *gui.Panel
	cc_physical_male_button     *gui.Button
	cc_physical_female_button   *gui.Button
	cc_physical_hair_left       *gui.Button
	cc_physical_hair_right      *gui.Button
	cc_physical_skin_left       *gui.Button
	cc_physical_skin_right      *gui.Button
	cc_physical_dwarf_button    *gui.Button
	cc_physical_elf_button      *gui.Button
	cc_physical_gnome_button    *gui.Button
	cc_physical_human_button    *gui.Button
	cc_physical_leshy_button    *gui.Button
	cc_physical_ogre_button     *gui.Button
	cc_physical_orc_button      *gui.Button
	cc_physical_back_button     *gui.Button
	cc_physical_next_button     *gui.Button
	cc_physical_quit_button     *gui.Button
	cc_points_menu              *gui.Panel
	cc_physical_profession_list *gui.List
	cc_points_attribute_panel   *gui.Panel
	cc_points_skill_panel       *gui.Panel
	cc_points_option_panel      *gui.Panel
	cc_points_back_button       *gui.Button
	cc_points_next_button       *gui.Button
	cc_points_quit_button       *gui.Button
	cc_final_menu               *gui.Panel
	cc_final_table              *gui.Table
	cc_final_back_button        *gui.Button
	cc_final_accept_button      *gui.Button
	cc_final_quit_button        *gui.Button

	// Game specific components
	assets_dir        string
	cursor            int
	login_password    string
	client_game_state uint8
}

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}

// SetupGui creates all user interface elements
func (ogs *OldentideClientGamestate) SetupGui(width, height int) {
	log.Debug("Creating GUI...")

	// Colors:
	//interface_style_brown_0 := math32.Color4{0.51, 0.40, 0.34, 1.0}
	//interface_style_brown_1 := math32.Color4{0.47, 0.35, 0.20, 1.0}
	interface_style_brown_2 := math32.Color4{0.30, 0.23, 0.18, 1.0}
	//interface_style_brown_3 := math32.Color4{0.19, 0.13, 0.09, 1.0}
	//interface_style_brown_4 := math32.Color4{0.31, 0.20, 0.12, 1.0}

	//interface_style_accent_0 := math32.Color4{0.22, 0.29, 0.29, 1.0}

	// Color Styles:
	//ss := gui.StyleDefault().Slider
	//ss.

	// Layout styles:
	g_2_layout := gui.NewGridLayout(2)
	g_2_layout.SetAlignH(gui.AlignCenter)
	g_2_layout.SetAlignV(gui.AlignCenter)
	h_layout := gui.NewHBoxLayout()
	h_layout.SetAlignH(gui.AlignWidth)
	v_layout := gui.NewVBoxLayout()
	v_layout.SetAlignV(gui.AlignHeight)

	// Login menu -------------------------------
	ogs.login_menu = gui.NewPanel(600, 300)
	ogs.login_menu.SetLayout(h_layout)
	ogs.login_menu.SetColor4(&interface_style_brown_2)
	ogs.login_menu.SetBorders(3, 3, 3, 3)
	ogs.login_menu.SetBordersColor4(&math32.Color4{0, 0, 0, 1.0})
	ogs.root.Subscribe(gui.OnResize, func(evname string, ev interface{}) {
		ogs.login_menu.SetPositionX((ogs.root.Width() - ogs.login_menu.Width()) / 2)
		ogs.login_menu.SetPositionY((ogs.root.Height() - ogs.login_menu.Height()) / 2)
	})

	login_left := gui.NewPanel(300, 300)
	login_left.SetLayout(v_layout)

	login_left.Add(gui.NewLabelWithFont("Username:", ogs.font))
	ogs.login_username = gui.NewEdit(250, "username")
	ogs.login_username.SetFontSize(16)
	ogs.login_username.SetPosition(15, 0)
	login_left.Add(ogs.login_username)

	login_left.Add(gui.NewLabelWithFont("Password:", ogs.font))
	ogs.login_password_edit = gui.NewEdit(250, "password")
	ogs.login_password_edit.SetFontSize(16)
	ogs.login_password_edit.Subscribe(gui.OnChar, func(name string, ev interface{}) {
		input_char := string(ev.(*window.CharEvent).Char)
		ogs.login_password += input_char
		ogs.login_password_edit.CursorBack()
		ogs.login_password_edit.CursorInput("*")
		fmt.Println("Typed something in password box.", ogs.login_password)
	})
	ogs.login_password_edit.Subscribe(gui.OnKeyDown, func(name string, ev interface{}) {
		kev := ev.(*window.KeyEvent)
		switch kev.Keycode {
		case window.KeyBackspace:
			if pwl := len(ogs.login_password) - 1; pwl >= 0 {
				ogs.login_password = ogs.login_password[:pwl]
			}
		case window.KeyEnter:
			fmt.Println("Enter pressed on password!!!")
			ogs.Login()
		}
	})
	login_left.Add(ogs.login_password_edit)

	login_buttons := gui.NewPanel(300, 40)
	login_buttons.SetLayout(h_layout)

	ogs.login_login_button = gui.NewButton("Login")
	ogs.login_login_button.Label.SetFontSize(16)
	ogs.login_login_button.Subscribe(gui.OnClick, func(name string, ev interface{}) {
		fmt.Println("Login button was pressed.")
		ogs.Login()
	})
	login_buttons.Add(ogs.login_login_button)

	ogs.login_quit_button = gui.NewButton("Quit")
	ogs.login_quit_button.Label.SetFontSize(16)
	ogs.login_quit_button.Subscribe(gui.OnClick, func(name string, ev interface{}) {
		ogs.Quit()
	})
	login_buttons.Add(ogs.login_quit_button)

	login_left.Add(login_buttons)

	login_right := gui.NewPanel(300, 300)
	login_right.SetLayout(v_layout)

	login_right.Add(gui.NewLabelWithFont("Server Address:", ogs.font))
	ogs.login_server_address = gui.NewEdit(250, "imp.oldentide.com")
	ogs.login_server_address.SetFontSize(16)
	ogs.login_server_address.SetText("imp.oldentide.com")
	login_right.Add(ogs.login_server_address)

	login_right.Add(gui.NewLabelWithFont("Server Web Port:", ogs.font))
	ogs.login_server_web_port = gui.NewEdit(250, "80")
	ogs.login_server_web_port.SetFontSize(16)
	ogs.login_server_web_port.SetText("80")
	login_right.Add(ogs.login_server_web_port)

	login_right.Add(gui.NewLabelWithFont("Server Game Port:", ogs.font))
	ogs.login_server_game_port = gui.NewEdit(250, "1337")
	ogs.login_server_game_port.SetFontSize(16)
	ogs.login_server_game_port.SetText("1337")
	login_right.Add(ogs.login_server_game_port)

	ogs.login_menu.Add(gui.NewPanel(25, 0))
	ogs.login_menu.Add(login_left)
	ogs.login_menu.Add(login_right)

	ogs.login_process = gui.NewPanel(400, 100)
	ogs.login_process.SetLayout(h_layout)
	ogs.login_process.SetColor4(&interface_style_brown_2)
	ogs.login_process.SetBorders(3, 3, 3, 3)
	ogs.login_process.SetBordersColor4(&math32.Color4{0, 0, 0, 1.0})
	ogs.root.Subscribe(gui.OnResize, func(evname string, ev interface{}) {
		ogs.login_process.SetPositionX((ogs.root.Width() - ogs.login_process.Width()) / 2)
		ogs.login_process.SetPositionY((ogs.root.Height() - ogs.login_process.Height()) / 2)
	})

	login_process_right := gui.NewPanel(375, 100)
	login_process_right.SetLayout(v_layout)

	login_process_right.Add(gui.NewLabelWithFont("Login Process:", ogs.font))
	ogs.login_process_slider = gui.NewHSlider(350, 35)
	ogs.login_process_slider.SetValue(0.0)
	ogs.login_process_slider.SetEnabled(false)
	ogs.login_process_slider.SetText(fmt.Sprintf("%3.0f", ogs.login_process_slider.Value()*100))
	login_process_right.Add(ogs.login_process_slider)
	ogs.login_process_status = gui.NewLabelWithFont("Waiting", ogs.font)
	login_process_right.Add(ogs.login_process_status)

	ogs.login_process.Add(gui.NewPanel(25, 0))
	ogs.login_process.Add(login_process_right)
	// ------------------------------------------

	// Character Select Menu --------------------
	ogs.cs_menu = gui.NewPanel(250, 400)
	ogs.cs_menu.SetLayout(v_layout)
	ogs.cs_menu.SetColor4(&interface_style_brown_2)
	ogs.cs_menu.SetBorders(3, 3, 3, 3)
	ogs.cs_menu.SetBordersColor4(&math32.Color4{0, 0, 0, 1.0})
	ogs.root.Subscribe(gui.OnResize, func(evname string, ev interface{}) {
		ogs.cs_menu.SetPositionX((ogs.root.Width() - ogs.cs_menu.Width()) / 2)
		ogs.cs_menu.SetPositionY((ogs.root.Height() - ogs.cs_menu.Height()) / 2)
	})

	cs_spacer_panel_top := gui.NewPanel(250, 10)
	ogs.cs_menu.Add(cs_spacer_panel_top)

	cs_list_panel := gui.NewPanel(250, 300)
	cs_list_panel.SetLayout(h_layout)

	ogs.cs_characters = gui.NewVList(200, 280)
	ogs.cs_characters.SetSingle(true)
	cs_list_panel.Add(ogs.cs_characters)

	ogs.cs_menu.Add(cs_list_panel)

	cs_spacer_panel_mid := gui.NewPanel(250, 10)
	ogs.cs_menu.Add(cs_spacer_panel_mid)

	cs_button_panel_top := gui.NewPanel(250, 50)
	cs_button_panel_top.SetLayout(h_layout)

	ogs.cs_enter_world_button = gui.NewButton("Enter World")
	ogs.cs_enter_world_button.Label.SetFontSize(16)
	ogs.cs_enter_world_button.Subscribe(gui.OnClick, func(name string, ev interface{}) {
		fmt.Println("Enter World button was pressed.")
		//ogs.EnterWorld()
	})
	cs_button_panel_top.Add(ogs.cs_enter_world_button)

	ogs.cs_create_character_button = gui.NewButton("Create Character")
	ogs.cs_create_character_button.Label.SetFontSize(16)
	ogs.cs_create_character_button.Subscribe(gui.OnClick, func(name string, ev interface{}) {
		fmt.Println("Create Character button was pressed.")
		ogs.CreateCharacter()
	})
	cs_button_panel_top.Add(ogs.cs_create_character_button)

	cs_button_panel_bottom := gui.NewPanel(250, 50)
	cs_button_panel_bottom.SetLayout(h_layout)

	ogs.cs_back_button = gui.NewButton("Back")
	ogs.cs_back_button.Label.SetFontSize(16)
	ogs.cs_back_button.Subscribe(gui.OnClick, func(name string, ev interface{}) {
		fmt.Println("Create Character Back button was pressed.")
		// Clear list and go back to login window.
	})
	cs_button_panel_bottom.Add(ogs.cs_back_button)

	ogs.cs_quit_button = gui.NewButton("Quit")
	ogs.cs_quit_button.Label.SetFontSize(16)
	ogs.cs_quit_button.Subscribe(gui.OnClick, func(name string, ev interface{}) {
		fmt.Println("Create Character Quit button was pressed.")
		ogs.Quit()
	})
	cs_button_panel_bottom.Add(ogs.cs_quit_button)

	ogs.cs_menu.Add(cs_button_panel_top)
	ogs.cs_menu.Add(cs_button_panel_bottom)
	// ------------------------------------------

	// Character Create Menu --------------------
	ogs.cc_physical_menu = gui.NewPanel(600, 400)
	ogs.cc_physical_menu.SetLayout(v_layout)
	ogs.cc_physical_menu.SetColor4(&interface_style_brown_2)
	ogs.cc_physical_menu.SetBorders(3, 3, 3, 3)
	ogs.cc_physical_menu.SetBordersColor4(&math32.Color4{0, 0, 0, 1.0})
	ogs.root.Subscribe(gui.OnResize, func(evname string, ev interface{}) {
		ogs.cc_physical_menu.SetPositionX((ogs.root.Width() - ogs.cc_physical_menu.Width()) / 2)
		ogs.cc_physical_menu.SetPositionY((ogs.root.Height() - ogs.cc_physical_menu.Height()) / 2)
	})

	cc_physical_header := gui.NewPanel(600, 20)
	cc_physical_header.SetLayout(h_layout)
	cc_physical_header.Add(gui.NewLabelWithFont("Character Creation", ogs.font))
	ogs.cc_physical_menu.Add(cc_physical_header)

	cc_physical_name_bar := gui.NewPanel(600, 30)
	cc_physical_name_bar.SetLayout(h_layout)
	cc_physical_name_bar.Add(gui.NewLabelWithFont("First Name :", ogs.font))
	ogs.cc_physical_first_name = gui.NewEdit(100, "")
	ogs.cc_physical_first_name.SetFontSize(16)
	cc_physical_name_bar.Add(ogs.cc_physical_first_name)
	ogs.cc_physical_last_name = gui.NewEdit(100, "")
	ogs.cc_physical_last_name.SetFontSize(16)
	cc_physical_name_bar.Add(ogs.cc_physical_last_name)
	cc_physical_name_bar.Add(gui.NewLabelWithFont(": Last Name", ogs.font))
	ogs.cc_physical_menu.Add(cc_physical_name_bar)

	cc_physical_main_bar := gui.NewPanel(600, 300)
	cc_physical_main_bar.SetLayout(h_layout)

	cc_physical_control_bar := gui.NewPanel(300, 300)
	cc_physical_control_bar.SetLayout(v_layout)

	cc_physical_hair_panel := gui.NewPanel(300, 30)
	cc_physical_hair_panel.SetLayout(h_layout)
	ogs.cc_physical_hair_left = gui.NewButton("Hair Left")
	ogs.cc_physical_hair_right = gui.NewButton("Hair Right")
	cc_physical_hair_panel.Add(ogs.cc_physical_hair_left)
	cc_physical_hair_panel.Add(ogs.cc_physical_hair_right)
	cc_physical_control_bar.Add(cc_physical_hair_panel)

	cc_physical_skin_panel := gui.NewPanel(300, 30)
	cc_physical_skin_panel.SetLayout(h_layout)
	ogs.cc_physical_skin_left = gui.NewButton("Race Left")
	ogs.cc_physical_skin_right = gui.NewButton("Race Left")
	cc_physical_skin_panel.Add(ogs.cc_physical_skin_left)
	cc_physical_skin_panel.Add(ogs.cc_physical_skin_right)
	cc_physical_control_bar.Add(cc_physical_skin_panel)

	cc_physical_human_panel := gui.NewPanel(300, 30)
	cc_physical_human_panel.SetLayout(h_layout)
	ogs.cc_physical_human_button = gui.NewButton("Human")
	cc_physical_human_panel.Add(ogs.cc_physical_human_button)
	cc_physical_control_bar.Add(cc_physical_human_panel)

	cc_physical_dwarf_elf_panel := gui.NewPanel(300, 30)
	cc_physical_dwarf_elf_panel.SetLayout(h_layout)
	ogs.cc_physical_dwarf_button = gui.NewButton("Dwarf")
	ogs.cc_physical_elf_button = gui.NewButton("Elf")
	cc_physical_dwarf_elf_panel.Add(ogs.cc_physical_dwarf_button)
	cc_physical_dwarf_elf_panel.Add(ogs.cc_physical_elf_button)
	cc_physical_control_bar.Add(cc_physical_dwarf_elf_panel)

	cc_physical_gnome_leshy_panel := gui.NewPanel(300, 30)
	cc_physical_gnome_leshy_panel.SetLayout(h_layout)
	ogs.cc_physical_gnome_button = gui.NewButton("Gnome")
	ogs.cc_physical_leshy_button = gui.NewButton("Leshy")
	cc_physical_gnome_leshy_panel.Add(ogs.cc_physical_gnome_button)
	cc_physical_gnome_leshy_panel.Add(ogs.cc_physical_leshy_button)
	cc_physical_control_bar.Add(cc_physical_gnome_leshy_panel)

	cc_physical_ogre_orc_panel := gui.NewPanel(300, 30)
	cc_physical_ogre_orc_panel.SetLayout(h_layout)
	ogs.cc_physical_ogre_button = gui.NewButton("Ogre")
	ogs.cc_physical_orc_button = gui.NewButton("Orc")
	cc_physical_ogre_orc_panel.Add(ogs.cc_physical_ogre_button)
	cc_physical_ogre_orc_panel.Add(ogs.cc_physical_orc_button)
	cc_physical_control_bar.Add(cc_physical_ogre_orc_panel)

	cc_physical_main_bar.Add(cc_physical_control_bar)

	cc_physical_preview_bar := gui.NewPanel(300, 300)
	cc_physical_main_bar.Add(cc_physical_preview_bar)

	ogs.cc_physical_menu.Add(cc_physical_main_bar)

	cc_physical_footer := gui.NewPanel(600, 50)
	cc_physical_footer.SetLayout(h_layout)
	ogs.cc_physical_back_button = gui.NewButton("Back")
	cc_physical_footer.Add(ogs.cc_physical_back_button)
	ogs.cc_physical_quit_button = gui.NewButton("Quit")
	cc_physical_footer.Add(ogs.cc_physical_quit_button)
	ogs.cc_physical_next_button = gui.NewButton("Next")
	cc_physical_footer.Add(ogs.cc_physical_next_button)

	ogs.cc_physical_menu.Add(cc_physical_footer)

	// ------------------------------------------

	// Dispatch a fake OnResize event to update all subscribed elements
	ogs.root.Dispatch(gui.OnResize, nil)

	log.Debug("Done creating GUI.")
}

func (ogs *OldentideClientGamestate) UpdateLoginStatus(pct float32, login_step string) {
	ogs.login_process_slider.SetValue(pct)
	ogs.login_process_slider.SetText(fmt.Sprintf("%3.0f", ogs.login_process_slider.Value()*100))
	ogs.login_process_status.SetText(login_step)
}

func (ogs *OldentideClientGamestate) Login() {
	if ogs.client_game_state != LOGIN_SCREEN {
		return
	}

	ogs.root.Remove(ogs.login_menu)
	ogs.login_menu.SetEnabled(false)
	ogs.root.Add(ogs.login_process)
	ogs.login_process.SetEnabled(true)

	steps := 5
	step := 0

	ogs.UpdateLoginStatus(float32(step)/float32(steps), "Extracting Credentials")
	step += 1
	fmt.Println("Username: ", ogs.login_username.Text())
	fmt.Println("Password: ", ogs.login_password)
	fmt.Println("Server Address: ", ogs.login_server_address.Text())
	fmt.Println("Server Web Port: ", ogs.login_server_web_port.Text())
	fmt.Println("Server Game Port: ", ogs.login_server_game_port.Text())

	ogs.UpdateLoginStatus(float32(step)/float32(steps), "Checking Login Status")
	step += 1
	login_server_page := "http://" + ogs.login_server_address.Text() + ":" + ogs.login_server_web_port.Text() + "/login"
	resp, err := http.PostForm(login_server_page, url.Values{"username": {ogs.login_username.Text()}, "password": {ogs.login_password}})
	if err != nil {
		ogs.root.Add(ogs.login_menu)
		ogs.login_menu.SetEnabled(true)
	}
	fmt.Println(resp)

	ogs.UpdateLoginStatus(float32(step)/float32(steps), "Saving Account Information")
	step += 1

	ogs.UpdateLoginStatus(float32(step)/float32(steps), "Loading Character List")
	step += 1

	ogs.root.Remove(ogs.login_menu) // Debug.
	ogs.login_menu.SetEnabled(false)
	ogs.root.Remove(ogs.login_process)
	ogs.login_process.SetEnabled(false)
	ogs.root.Add(ogs.cs_menu)
	ogs.cs_menu.SetEnabled(true)
	ogs.cs_characters.Add(gui.NewLabelWithFont("Character_1", ogs.font))
	ogs.cs_characters.Add(gui.NewLabelWithFont("Character_2", ogs.font))
	ogs.cs_characters.Add(gui.NewLabelWithFont("Character_3", ogs.font))
	ogs.cs_characters.Add(gui.NewLabelWithFont("Character_4", ogs.font))
	stop := false
	for stop == false {
		if ogs.cs_characters.Selected() != nil {
			//fmt.Println(ogs.cs_characters.Selected().item.Text())
			stop = true
			/*if (ogs.cs_characters.Selected()[0].Text() == "Character_4") {
				stop = true
			}*/
		}
	}
}

func (ogs *OldentideClientGamestate) CreateCharacter() {
	ogs.root.Remove(ogs.cs_menu)
	ogs.cs_menu.SetEnabled(false)
	ogs.root.Add(ogs.cc_physical_menu)
	ogs.cs_menu.SetEnabled(true)
}

// Quit saves the user data and quits the game
func (ogs *OldentideClientGamestate) Quit() {
	fmt.Println("Quit.")
	// Stop audio.
	ogs.loginMusicPlayer.Stop()
	// Close the window
	ogs.win.SetShouldClose(true)
}

// LoadSkybox loads a space skybox and adds it to the scene
func (ogs *OldentideClientGamestate) LoadSkyBox(skybox_name string, file_format string) {
	log.Debug("Creating Skybox...")

	// Load skybox textures.
	skyboxDir := (ogs.assets_dir + "/Textures/Skyboxes/" + skybox_name + "/")
	skyboxData := graphic.SkyboxData{skyboxDir, file_format, [6]string{"px", "nx", "py", "ny", "pz", "nz"}}
	skybox, err := graphic.NewSkybox(skyboxData)
	checkErr(err)

	// Add skybox to scene.
	skybox.SetRenderOrder(-1) // The skybox should always be rendered first
	ogs.scene.Add(skybox)

	log.Debug("Done creating skybox")
}

// Attemplts to load audio libraries (from .dll).
func loadAudioLibs() error {
	// Open default audio device
	dev, err := al.OpenDevice("")
	if dev == nil {
		return fmt.Errorf("Error: %s opening OpenAL default device", err)
	}

	// Create audio context
	acx, err := al.CreateContext(dev, nil)
	if err != nil {
		return fmt.Errorf("Error creating audio context:%s", err)
	}

	// Make the context the current one
	err = al.MakeContextCurrent(acx)
	if err != nil {
		return fmt.Errorf("Error setting audio context current:%s", err)
	}

	log.Debug("%s version: %s", al.GetString(al.Vendor), al.GetString(al.Version))
	log.Debug("%s", vorbis.VersionString())
	return nil
}

// LoadAudio loads music and sound effects
func (ogs *OldentideClientGamestate) LoadAudio() {
	log.Debug("Load Audio")

	// Create listener and add it to the current camera
	listener := audio.NewListener()
	cdir := ogs.camera.Direction()
	listener.SetDirectionVec(&cdir)
	ogs.camera.GetCamera().Add(listener)

	// Helper function to create player and handle errors
	createPlayer := func(fname string) *audio.Player {
		log.Debug("Loading " + fname)
		p, err := audio.NewPlayer(fname)
		if err != nil {
			log.Error("Failed to create player for: %v", fname)
		}
		return p
	}

	// Load each music file you want to use into memory here. (Be a hog, they are small files!)
	ogs.loginMusicPlayer = createPlayer(ogs.assets_dir + "/Music/Komiku__End_of_the_trip.ogg")
	ogs.loginMusicPlayer.SetGain(0.05)
	ogs.loginMusicPlayer.SetLooping(false)
}

// Update updates the current level if any
func (ogs *OldentideClientGamestate) Update(timeDelta float64) {
	return
}

// ToggleFullScreen toggles whether is game is fullscreen or windowed
func (ogs *OldentideClientGamestate) ToggleFullScreen() {
	log.Debug("Toggle FullScreen")
	ogs.win.SetFullScreen(!ogs.win.FullScreen())
}

// onKey handles keyboard events for the game
func (ogs *OldentideClientGamestate) onKey(evname string, ev interface{}) {
	if ogs.client_game_state == IN_WORLD {
		kev := ev.(*window.KeyEvent)
		switch kev.Keycode {
		case window.KeyEscape:
			fmt.Println("Escape Key Pressed.")
		case window.KeyP:
			fmt.Println("P Key Pressed.") // Bring up party menu.
		case window.KeyC:
			fmt.Println("C Key Pressed.") // Bring up character menu.
		case window.KeyI:
			fmt.Println("I Key Pressed.") // Bring up inventory menu.
		case window.KeySlash:
			fmt.Println("/ Key Pressed.") // Focus the chat window and write "/".
		case window.KeyM:
			fmt.Println("M Key Pressed.") // Bring up the map.
		case window.KeyB:
			fmt.Println("B Key Pressed.") // Bring up the spellbook (spells and manuevers).
		}
	}
}

// onMouse handles mouse events for the game
func (ogs *OldentideClientGamestate) onMouse(evname string, ev interface{}) {
	mev := ev.(*window.MouseEvent)
	fmt.Println(mev)
}

// onCursor handles cursor movement for the game
func (ogs *OldentideClientGamestate) onCursor(evname string, ev interface{}) {
	// Calculate direction of potential movement based on camera angle
	var dir math32.Vector3
	ogs.camera.WorldDirection(&dir)
	ogs.stepDelta.Set(0, 0)

	if math32.Abs(dir.Z) > math32.Abs(dir.X) {
		if dir.Z > 0 {
			ogs.stepDelta.Y = 1
		} else {
			ogs.stepDelta.Y = -1
		}
	} else {
		if dir.X > 0 {
			ogs.stepDelta.X = 1
		} else {
			ogs.stepDelta.X = -1
		}
	}
}

// RenderFrame renders a frame of the scene with the GUI overlaid
func (ogs *OldentideClientGamestate) RenderFrame() {

	// Process GUI timers
	ogs.root.TimerManager.ProcessTimers()

	// Render the scene/gui using the specified camera
	rendered, err := ogs.renderer.Render(ogs.camera)
	checkErr(err)

	// Check I/O events
	ogs.wmgr.PollEvents()

	// Update window if necessary
	if rendered {
		ogs.win.SwapBuffers()
	}
}

func main() {
	runtime.LockOSThread() // OpenGL functions must be executed in the same thread as window.New()

	// Parse command line flags
	showLog := flag.Bool("debug", false, "display the debug log")
	flag.Parse()

	// Create logger
	log = logger.New("Oldentide", nil)
	log.AddWriter(logger.NewConsole(false))
	log.SetFormat(logger.FTIME | logger.FMICROS)
	if *showLog == true {
		log.SetLevel(logger.DEBUG)
	} else {
		log.SetLevel(logger.INFO)
	}
	log.Info("Initializing Oldentide")

	// Create Client Gamestate struct
	ogs := new(OldentideClientGamestate)

	// Manually scan the $GOPATH directories to find the data directory
	rawPaths := os.Getenv("GOPATH")
	paths := strings.Split(rawPaths, ":")
	for _, j := range paths {
		// Checks Assets path
		path := filepath.Join(j, "../Assets")
		if _, err := os.Stat(path); err == nil {
			ogs.assets_dir = path
		}
	}

	// Get the window manager
	var err error
	ogs.wmgr, err = window.Manager("glfw")
	checkErr(err)

	// Create window and OpenGL context
	ogs.win, err = ogs.wmgr.CreateWindow(1280, 720, "Oldentide", false)
	checkErr(err)

	// Set window icon.
	// ogs.wmgr.

	// Create OpenGL state
	ogs.gs, err = gls.New()
	checkErr(err)

	// Set Cursor to Oldentide Cursor
	ogs.cursor, err = ogs.wmgr.CreateCursor(ogs.assets_dir+"/Interface/OldentideCursor30.png", 0, 0)
	if err != nil {
		fmt.Println("Error creating cursor.")
		//log.Log().Fatal("Error creating cursor: %s", err)
	}
	ogs.win.SetCustomCursor(ogs.cursor)

	// Build Font
	ogs.font, err = text.NewFont(ogs.assets_dir + "/Fonts/Sitka.ttf")
	checkErr(err)

	// Speed up a bit by not checking OpenGL errors
	ogs.gs.SetCheckErrors(false)

	// Sets window background color
	ogs.gs.ClearColor(0.1, 0.1, 0.1, 1.0)

	// Sets the OpenGL viewport size the same as the window size
	// This normally should be updated if the window is resized.
	width, height := ogs.win.Size()
	ogs.gs.Viewport(0, 0, int32(width), int32(height))

	// Creates GUI root panel
	ogs.root = gui.NewRoot(ogs.gs, ogs.win)
	ogs.root.SetSize(float32(width), float32(height))

	// Subscribe to window resize events. When the window is resized:
	// - Update the viewport size
	// - Update the root panel size
	// - Update the camera aspect ratio
	ogs.win.Subscribe(window.OnWindowSize, func(evname string, ev interface{}) {
		width, height := ogs.win.Size()
		ogs.gs.Viewport(0, 0, int32(width), int32(height))
		ogs.root.SetSize(float32(width), float32(height))
		aspect := float32(width) / float32(height)
		ogs.camera.SetAspect(aspect)
	})

	// Subscribe window to events
	ogs.win.Subscribe(window.OnKeyDown, ogs.onKey)
	ogs.win.Subscribe(window.OnMouseUp, ogs.onMouse)
	ogs.win.Subscribe(window.OnMouseDown, ogs.onMouse)

	// Creates a renderer and adds default shaders
	ogs.renderer = renderer.NewRenderer(ogs.gs)
	//ogs.renderer.SetSortObjects(false)
	err = ogs.renderer.AddDefaultShaders()
	checkErr(err)
	ogs.renderer.SetGui(ogs.root)

	// Adds a perspective camera to the scene
	// The camera aspect ratio should be updated if the window is resized.
	aspect := float32(width) / float32(height)
	ogs.camera = camera.NewPerspective(65, aspect, 0.01, 1000)
	ogs.camera.SetPosition(0, 4, 5)
	ogs.camera.LookAt(&math32.Vector3{0, 5, 0})

	// Create orbit control and set limits
	ogs.orbit_control = control.NewOrbitControl(ogs.camera, ogs.win)
	ogs.orbit_control.Enabled = false
	ogs.orbit_control.EnablePan = false
	ogs.orbit_control.MaxPolarAngle = 2 * math32.Pi / 3
	ogs.orbit_control.MinDistance = 5
	ogs.orbit_control.MaxDistance = 15

	// Create main scene and child levelScene
	ogs.scene = core.NewNode()
	ogs.levelScene = core.NewNode()
	ogs.scene.Add(ogs.camera)
	ogs.scene.Add(ogs.levelScene)
	ogs.stepDelta = math32.NewVector2(0, 0)
	ogs.renderer.SetScene(ogs.scene)

	// Add white ambient light to the scene
	ambLight := light.NewAmbient(&math32.Color{1.0, 1.0, 1.0}, 0.4)
	ogs.scene.Add(ambLight)

	ogs.SetupGui(width, height)
	ogs.RenderFrame()

	// Try to open audio libraries
	err = loadAudioLibs()
	if err != nil {
		log.Error("%s", err)
	} else {
		ogs.LoadAudio()
		// Queue the music!
		ogs.loginMusicPlayer.Play()
	}

	ogs.LoadSkyBox("Blue_Clouds", "jpg")
	//ogs.LoadSkyBox("Sunny_High_Plains", "jpg")

	ogs.win.Subscribe(window.OnCursor, ogs.onCursor)

	// Done Loading - Show login window.
	ogs.client_game_state = LOGIN_SCREEN
	ogs.root.Add(ogs.login_menu)

	now := time.Now()
	newNow := time.Now()
	log.Info("Starting Render Loop")

	// Start the render loop
	for !ogs.win.ShouldClose() {

		newNow = time.Now()
		timeDelta := now.Sub(newNow)
		now = newNow
		//ogs.last_camera_angle.Copy(*ogs.camera.Target())
		//ogs.last_camera_angle.X += 1
		if ogs.client_game_state == LOGIN_SCREEN ||
			ogs.client_game_state == CHARACTER_SELECT ||
			ogs.client_game_state == CHARACTER_CREATION_PHYSICAL ||
			ogs.client_game_state == CHARACTER_CREATION_POINTS ||
			ogs.client_game_state == CHARACTER_CREATION_FINAL ||
			ogs.client_game_state == LOADING {
			lca := ogs.camera.Target()
			fmt.Println(lca)
			lca.X += 0.001
			ogs.camera.LookAt(&lca)
		}
		ogs.Update(timeDelta.Seconds())
		ogs.RenderFrame()
	}
}
