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
	CHARACTER_CREATION_SKILLS   uint8 = iota
	CHARACTER_CREATION_FINAL    uint8 = iota
	LOADING                     uint8 = iota
	IN_WORLD                    uint8 = iota
)

type OldentideClientGamestate struct {
	// g3n window and engine components
	wmgr          window.IWindowManager
	win           window.IWindow
	gs            *gls.GLS
	renderer      *renderer.Renderer
	scene         *core.Node
	camera        *camera.Perspective
	orbit_control *control.OrbitControl
	stepDelta     *math32.Vector2
	levelScene    *core.Node

	// Sound & Music players
	loginMusicPlayer *audio.Player

	// Gui components
	root                   *gui.Root
	login_menu             *gui.Panel
	login_username         *gui.Edit
	login_password_edit    *gui.Edit
	login_server_address   *gui.Edit
	login_server_web_port  *gui.Edit
	login_server_game_port *gui.Edit
	login_login_button     *gui.Button
	login_quit_button      *gui.Button
	login_process          *gui.Panel
	login_process_slider   *gui.Slider
	login_process_status   *gui.Label

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
		ogs.login_menu.SetPositionY((ogs.root.Height()-ogs.login_menu.Height()) / 2 + 100)
	})

	login_left := gui.NewPanel(300, 300)
	login_left.SetLayout(v_layout)

	login_left.Add(gui.NewLabel("Username:"))
	ogs.login_username = gui.NewEdit(250, "username")
	ogs.login_username.SetFontSize(16)
	ogs.login_username.SetPosition(15, 0)
	login_left.Add(ogs.login_username)

	login_left.Add(gui.NewLabel("Password:"))
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

	login_right.Add(gui.NewLabel("Server Address:"))
	ogs.login_server_address = gui.NewEdit(250, "imp.oldentide.com")
	ogs.login_server_address.SetFontSize(16)
	ogs.login_server_address.SetText("imp.oldentide.com")
	login_right.Add(ogs.login_server_address)

	login_right.Add(gui.NewLabel("Server Web Port:"))
	ogs.login_server_web_port = gui.NewEdit(250, "80")
	ogs.login_server_web_port.SetFontSize(16)
	ogs.login_server_web_port.SetText("80")
	login_right.Add(ogs.login_server_web_port)

	login_right.Add(gui.NewLabel("Server Game Port:"))
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

	login_process_right.Add(gui.NewLabel("Login Process:"))
	ogs.login_process_slider = gui.NewHSlider(350, 35)
	ogs.login_process_slider.SetValue(0.0)
	ogs.login_process_slider.SetEnabled(false)
	ogs.login_process_slider.SetText(fmt.Sprintf("%3.0f", ogs.login_process_slider.Value() * 100))
	login_process_right.Add(ogs.login_process_slider)
	ogs.login_process_status = gui.NewLabel("Waiting")
	login_process_right.Add(ogs.login_process_status)

	ogs.login_process.Add(gui.NewPanel(25, 0))
	ogs.login_process.Add(login_process_right)
	// ------------------------------------------

	// Dispatch a fake OnResize event to update all subscribed elements
	ogs.root.Dispatch(gui.OnResize, nil)

	log.Debug("Done creating GUI.")
}

func (ogs *OldentideClientGamestate) UpdateLoginStatus(pct float32, login_step string) {
	ogs.login_process_slider.SetValue(pct)
	ogs.login_process_slider.SetText(fmt.Sprintf("%3.0f", ogs.login_process_slider.Value() * 100))
	ogs.login_process_status.SetText(login_step)
}

func (ogs *OldentideClientGamestate) Login() {
	if ogs.client_game_state != LOGIN_SCREEN {
		return
	}

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
	if (err != nil) {
		ogs.root.Add(ogs.login_menu)	
	}
	fmt.Println(resp)

	ogs.UpdateLoginStatus(float32(step)/float32(steps), "Saving Account Information")
	step += 1

	ogs.UpdateLoginStatus(float32(step)/float32(steps), "Loading Character List")	
	step += 1
	ogs.root.Remove(ogs.login_menu)
	ogs.root.Add(ogs.login_process)
	//ogs.root.Add(ogs.login_menu)
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
	ogs.camera.LookAt(&math32.Vector3{0, 0, 0})

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

		ogs.Update(timeDelta.Seconds())
		ogs.RenderFrame()
	}
}
