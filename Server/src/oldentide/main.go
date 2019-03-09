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
func (g *OldentideClientGamestate) SetupGui(width, height int) {
	log.Debug("Creating GUI...")

	interface_component_background_color := math32.Color4{50.6, 40.4, 34.1, 1.0}

	//s := gui.StyleDefault()

	//var err error

	// Menu
	g.menu = gui.NewPanel(100, 100)
	g.menu.SetColor4(&math32.Color4{0.1, 0.1, 0.1, 0.6})
	g.root.Subscribe(gui.OnResize, func(evname string, ev interface{}) {
		g.menu.SetWidth(g.root.ContentWidth())
		g.menu.SetHeight(g.root.ContentHeight())
	})

	// Main panel
	g.main = gui.NewPanel(600, 300)
	mainLayout := gui.NewVBoxLayout()
	mainLayout.SetAlignV(gui.AlignHeight)
	g.main.SetLayout(mainLayout)
	g.main.SetBorders(2, 2, 2, 2)
	g.main.SetBordersColor4(&math32.Color4{0, 0, 0, 1.0})
	g.main.SetColor4(&interface_component_background_color)
	g.root.Subscribe(gui.OnResize, func(evname string, ev interface{}) {
		g.main.SetPositionX((g.root.Width() - g.main.Width()) / 2)
		g.main.SetPositionY((g.root.Height()-g.main.Height())/2 + 50)
	})

	/*
	topRow := gui.NewPanel(g.main.ContentWidth(), 100)
	topRowLayout := gui.NewHBoxLayout()
	topRowLayout.SetAlignH(gui.AlignWidth)
	topRow.SetLayout(topRowLayout)
	alignCenterVerical := gui.HBoxLayoutParams{Expand: 0, AlignV: gui.AlignCenter}
	*/

	g.root.Add(g.menu)

	// Dispatch a fake OnResize event to update all subscribed elements
	g.root.Dispatch(gui.OnResize, nil)

	log.Debug("Done creating GUI.")
}

// Update updates the current level if any
func (g *OldentideClientGamestate) Update(timeDelta float64) {
	return
}

// ToggleFullScreen toggles whether is game is fullscreen or windowed
func (g *OldentideClientGamestate) ToggleFullScreen() {
	log.Debug("Toggle FullScreen")
	g.win.SetFullScreen(!g.win.FullScreen())
}

// onKey handles keyboard events for the game
func (g *OldentideClientGamestate) onKey(evname string, ev interface{}) {
	kev := ev.(*window.KeyEvent)
	switch kev.Keycode {
	case window.KeyEscape:
		fmt.Println("Escape Key Pressed.")
	}
}

// onMouse handles mouse events for the game
func (g *OldentideClientGamestate) onMouse(evname string, ev interface{}) {
	mev := ev.(*window.MouseEvent)
	/*if g.gopherLocked == false && g.leveln > 0 {
		// Mouse button pressed
		if mev.Action == window.Press {
			// Left button pressed
			if mev.Button == window.MouseButtonLeft {
				g.arrowNode.SetVisible(true)
			}
		} else if mev.Action == window.Release {
			g.arrowNode.SetVisible(false)
		}
	}*/
	fmt.Println(mev)
}

// onCursor handles cursor movement for the game
func (g *OldentideClientGamestate) onCursor(evname string, ev interface{}) {
	// Calculate direction of potential movement based on camera angle
	var dir math32.Vector3
	g.camera.WorldDirection(&dir)
	g.stepDelta.Set(0, 0)

	if math32.Abs(dir.Z) > math32.Abs(dir.X) {
		if dir.Z > 0 {
			g.stepDelta.Y = 1
		} else {
			g.stepDelta.Y = -1
		}
	} else {
		if dir.X > 0 {
			g.stepDelta.X = 1
		} else {
			g.stepDelta.X = -1
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
	g := new(OldentideClientGamestate)

	// Manually scan the $GOPATH directories to find the data directory
	rawPaths := os.Getenv("GOPATH")
	paths := strings.Split(rawPaths, ":")
	for _, j := range paths {
		// Checks Assets path
		path := filepath.Join(j, "../Assets")
		if _, err := os.Stat(path); err == nil {
			g.assets_dir = path
		}
	}

	// Get the window manager
	var err error
	g.wmgr, err = window.Manager("glfw")
	if err != nil {
		panic(err)
	}

	// Create window and OpenGL context
	g.win, err = g.wmgr.CreateWindow(1280, 720, "Oldentide", false)
	if err != nil {
		panic(err)
	}

	// Set window icon.
	// g.wmgr.

	// Create OpenGL state
	g.gs, err = gls.New()
	if err != nil {
		panic(err)
	}

	// Set Cursor to Oldentide Cursor
	g.cursor, err = g.wmgr.CreateCursor(g.assets_dir + "/Interface/OldentideCursor30.png", 0, 0)
	if err != nil {
		fmt.Println("Error creating cursor.")
		//log.Log().Fatal("Error creating cursor: %s", err)
	}
	g.win.SetCustomCursor(g.cursor)

	// Speed up a bit by not checking OpenGL errors
	g.gs.SetCheckErrors(false)

	// Sets window background color
	g.gs.ClearColor(0.1, 0.1, 0.1, 1.0)

	// Sets the OpenGL viewport size the same as the window size
	// This normally should be updated if the window is resized.
	width, height := g.win.Size()
	g.gs.Viewport(0, 0, int32(width), int32(height))

	// Creates GUI root panel
	g.root = gui.NewRoot(g.gs, g.win)
	g.root.SetSize(float32(width), float32(height))

	// Subscribe to window resize events. When the window is resized:
	// - Update the viewport size
	// - Update the root panel size
	// - Update the camera aspect ratio
	g.win.Subscribe(window.OnWindowSize, func(evname string, ev interface{}) {
		width, height := g.win.Size()
		g.gs.Viewport(0, 0, int32(width), int32(height))
		g.root.SetSize(float32(width), float32(height))
		aspect := float32(width) / float32(height)
		g.camera.SetAspect(aspect)
	})

	// Subscribe window to events
	g.win.Subscribe(window.OnKeyDown, g.onKey)
	g.win.Subscribe(window.OnMouseUp, g.onMouse)
	g.win.Subscribe(window.OnMouseDown, g.onMouse)

	// Creates a renderer and adds default shaders
	g.renderer = renderer.NewRenderer(g.gs)
	//g.renderer.SetSortObjects(false)
	err = g.renderer.AddDefaultShaders()
	if err != nil {
		panic(err)
	}
	g.renderer.SetGui(g.root)

	// Adds a perspective camera to the scene
	// The camera aspect ratio should be updated if the window is resized.
	aspect := float32(width) / float32(height)
	g.camera = camera.NewPerspective(65, aspect, 0.01, 1000)
	g.camera.SetPosition(0, 4, 5)
	g.camera.LookAt(&math32.Vector3{0, 0, 0})

	// Create orbit control and set limits
	g.orbit_control = control.NewOrbitControl(g.camera, g.win)
	g.orbit_control.Enabled = false
	g.orbit_control.EnablePan = false
	g.orbit_control.MaxPolarAngle = 2 * math32.Pi / 3
	g.orbit_control.MinDistance = 5
	g.orbit_control.MaxDistance = 15

	// Create main scene and child levelScene
	g.scene = core.NewNode()
	//g.levelScene = core.NewNode()
	g.scene.Add(g.camera)
	//g.scene.Add(g.levelScene)
	g.stepDelta = math32.NewVector2(0, 0)
	g.renderer.SetScene(g.scene)

	// Add white ambient light to the scene
	ambLight := light.NewAmbient(&math32.Color{1.0, 1.0, 1.0}, 0.4)
	g.scene.Add(ambLight)

	//g.levelStyle = NewStandardStyle(g.assets_dir)

	g.SetupGui(width, height)
	g.RenderFrame()

/*
	// Try to open audio libraries
	err = loadAudioLibs()
	if err != nil {
		log.Error("%s", err)
		g.UpdateMusicButton(false)
		g.UpdateSfxButton(false)
		g.musicButton.SetEnabled(false)
		g.sfxButton.SetEnabled(false)
	} else {
		g.audioAvailable = true
		g.LoadAudio()
		g.UpdateMusicButton(g.userData.MusicOn)
		g.UpdateSfxButton(g.userData.SfxOn)

		// Queue the music!
		g.musicPlayerMenu.Play()
	}

	g.LoadSkyBox()
	g.LoadGopher()
	g.CreateArrowNode()
	g.LoadLevels()

	g.win.Subscribe(window.OnCursor, g.onCursor)

	if g.userData.LastUnlockedLevel == len(g.levels) {
		g.titleImage.SetImage(gui.ButtonDisabled, g.assets_dir + "/gui/title3_completed.png")
	}

	// Done Loading - hide the loading label, show the menu, and initialize the level
	g.loadingLabel.SetVisible(false)
	g.menu.Add(g.main)
	g.InitLevel(g.userData.LastLevel)
	g.gopherLocked = true
*/
	now := time.Now()
	newNow := time.Now()
	log.Info("Starting Render Loop")

	// Start the render loop
	for !g.win.ShouldClose() {

		newNow = time.Now()
		timeDelta := now.Sub(newNow)
		now = newNow

		g.Update(timeDelta.Seconds())
		g.RenderFrame()
	}
}

// RenderFrame renders a frame of the scene with the GUI overlaid
func (g *OldentideClientGamestate) RenderFrame() {

	// Process GUI timers
	g.root.TimerManager.ProcessTimers()

	// Render the scene/gui using the specified camera
	rendered, err := g.renderer.Render(g.camera)
	if err != nil {
		panic(err)
	}

	// Check I/O events
	g.wmgr.PollEvents()

	// Update window if necessary
	if rendered {
		g.win.SwapBuffers()
	}
}