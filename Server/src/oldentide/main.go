// Filename:    main.go
// Author:      Joseph DeVictoria
// Date:        Mar_7_2019

package main

import (
	_ "github.com/g3n/engine/audio"
	_ "github.com/g3n/engine/audio/al"
	_ "github.com/g3n/engine/audio/vorbis"
	"github.com/g3n/engine/camera"
	"github.com/g3n/engine/camera/control"
	"github.com/g3n/engine/core"
	"github.com/g3n/engine/gls"
	_ "github.com/g3n/engine/graphic"
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
	"runtime"
	_ "strconv"
	"time"
	"os"
	"strings"
	"path/filepath"
)

var log *logger.Logger

type OldentideClientGamestate struct {
	wmgr          window.IWindowManager
	win           window.IWindow
	gs            *gls.GLS
	renderer      *renderer.Renderer
	scene         *core.Node
	camera        *camera.Perspective
	orbit_control *control.OrbitControl
	assets_dir	  string
	root          *gui.Root
	menu          *gui.Panel
	main          *gui.Panel
	controls      *gui.Panel
	cursor 	      int
	stepDelta     *math32.Vector2
}

// SetupGui creates all user interface elements
func (ogs *OldentideClientGamestate) SetupGui(width, height int) {
	log.Debug("Creating GUI...")

	interface_component_background_color := math32.Color4{50.6, 40.4, 34.1, 1.0}

	//s := gui.StyleDefault()

	//var err error

	// Menu
	ogs.menu = gui.NewPanel(100, 100)
	ogs.menu.SetColor4(&math32.Color4{0.1, 0.1, 0.1, 0.6})
	ogs.root.Subscribe(gui.OnResize, func(evname string, ev interface{}) {
		ogs.menu.SetWidth(ogs.root.ContentWidth())
		ogs.menu.SetHeight(ogs.root.ContentHeight())
	})

	// Main panel
	ogs.main = gui.NewPanel(600, 300)
	mainLayout := gui.NewVBoxLayout()
	mainLayout.SetAlignV(gui.AlignHeight)
	ogs.main.SetLayout(mainLayout)
	ogs.main.SetBorders(2, 2, 2, 2)
	ogs.main.SetBordersColor4(&math32.Color4{0, 0, 0, 1.0})
	ogs.main.SetColor4(&interface_component_background_color)
	ogs.root.Subscribe(gui.OnResize, func(evname string, ev interface{}) {
		ogs.main.SetPositionX((ogs.root.Width() - ogs.main.Width()) / 2)
		ogs.main.SetPositionY((ogs.root.Height()-ogs.main.Height())/2 + 50)
	})

	/*
	topRow := gui.NewPanel(ogs.main.ContentWidth(), 100)
	topRowLayout := gui.NewHBoxLayout()
	topRowLayout.SetAlignH(gui.AlignWidth)
	topRow.SetLayout(topRowLayout)
	alignCenterVerical := gui.HBoxLayoutParams{Expand: 0, AlignV: gui.AlignCenter}
	*/

	ogs.root.Add(ogs.menu)

	// Dispatch a fake OnResize event to update all subscribed elements
	ogs.root.Dispatch(gui.OnResize, nil)

	log.Debug("Done creating GUI.")
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
	kev := ev.(*window.KeyEvent)
	switch kev.Keycode {
	case window.KeyEscape:
		fmt.Println("Escape Key Pressed.")
	}
}

// onMouse handles mouse events for the game
func (ogs *OldentideClientGamestate) onMouse(evname string, ev interface{}) {
	mev := ev.(*window.MouseEvent)
	/*if ogs.gopherLocked == false && ogs.leveln > 0 {
		// Mouse button pressed
		if mev.Action == window.Press {
			// Left button pressed
			if mev.Button == window.MouseButtonLeft {
				ogs.arrowNode.SetVisible(true)
			}
		} else if mev.Action == window.Release {
			ogs.arrowNode.SetVisible(false)
		}
	}*/
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

func main() {
	// OpenGL functions must be executed in the same thread where
	// the context was created (by window.New())
	runtime.LockOSThread()

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
	if err != nil {
		panic(err)
	}

	// Create window and OpenGL context
	ogs.win, err = ogs.wmgr.CreateWindow(1280, 720, "Oldentide", false)
	if err != nil {
		panic(err)
	}

	// Set window icon.
	// ogs.wmgr.

	// Create OpenGL state
	ogs.gs, err = gls.New()
	if err != nil {
		panic(err)
	}

	// Set Cursor to Oldentide Cursor
	ogs.cursor, err = ogs.wmgr.CreateCursor(ogs.assets_dir + "/Interface/OldentideCursor30.png", 0, 0)
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
	if err != nil {
		panic(err)
	}
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
	//ogs.levelScene = core.NewNode()
	ogs.scene.Add(ogs.camera)
	//ogs.scene.Add(ogs.levelScene)
	ogs.stepDelta = math32.NewVector2(0, 0)
	ogs.renderer.SetScene(ogs.scene)

	// Add white ambient light to the scene
	ambLight := light.NewAmbient(&math32.Color{1.0, 1.0, 1.0}, 0.4)
	ogs.scene.Add(ambLight)

	//ogs.levelStyle = NewStandardStyle(ogs.assets_dir)

	ogs.SetupGui(width, height)
	ogs.RenderFrame()

/*
	// Try to open audio libraries
	err = loadAudioLibs()
	if err != nil {
		log.Error("%s", err)
		ogs.UpdateMusicButton(false)
		ogs.UpdateSfxButton(false)
		ogs.musicButton.SetEnabled(false)
		ogs.sfxButton.SetEnabled(false)
	} else {
		ogs.audioAvailable = true
		ogs.LoadAudio()
		ogs.UpdateMusicButton(ogs.userData.MusicOn)
		ogs.UpdateSfxButton(ogs.userData.SfxOn)

		// Queue the music!
		ogs.musicPlayerMenu.Play()
	}

	ogs.LoadSkyBox()
	ogs.LoadGopher()
	ogs.CreateArrowNode()
	ogs.LoadLevels()

	ogs.win.Subscribe(window.OnCursor, ogs.onCursor)

	if ogs.userData.LastUnlockedLevel == len(ogs.levels) {
		ogs.titleImage.SetImage(gui.ButtonDisabled, ogs.assets_dir + "/gui/title3_completed.png")
	}

	// Done Loading - hide the loading label, show the menu, and initialize the level
	ogs.loadingLabel.SetVisible(false)
	ogs.menu.Add(ogs.main)
	ogs.InitLevel(ogs.userData.LastLevel)
	ogs.gopherLocked = true
*/
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

// RenderFrame renders a frame of the scene with the GUI overlaid
func (ogs *OldentideClientGamestate) RenderFrame() {

	// Process GUI timers
	ogs.root.TimerManager.ProcessTimers()

	// Render the scene/gui using the specified camera
	rendered, err := ogs.renderer.Render(ogs.camera)
	if err != nil {
		panic(err)
	}

	// Check I/O events
	ogs.wmgr.PollEvents()

	// Update window if necessary
	if rendered {
		ogs.win.SwapBuffers()
	}
}