#include "cGAY/renderer.h"
#include "cGAY/resources.h"
#include "cGAY/window.h"
// #include <AppCore/App.h>
// #include <AppCore/Overlay.h>
// #include <AppCore/Window.h>

// using namespace ultralight;

// class MyApp : public WindowListener, public ViewListener {
//   RefPtr<App> app_;
//   RefPtr<Window> window_;
//   RefPtr<Overlay> overlay_;

// public:
//   MyApp() {
//     ///
//     /// Create our main App instance.
//     ///
//     /// The App class is responsible for the lifetime of the application and is required to create
//     /// any windows.
//     ///
//     app_ = App::Create();

//     ///
//     /// Create our Window.
//     ///
//     /// This command creates a native platform window and shows it immediately.
//     ///
//     /// The window's size (900 by 600) is in virtual device coordinates, the actual size in pixels
//     /// is automatically determined by the monitor's DPI.
//     ///
//     window_ = Window::Create(app_->main_monitor(), 900, 600, false, kWindowFlags_Titled);

//     ///
//     /// Set the title of our window.
//     ///
//     window_->SetTitle("Ultralight Sample 2 - Basic App");

//     ///
//     /// Create a web-content overlay that spans the entire window.
//     ///
//     /// You can create multiple overlays per window, each overlay has its own View which can be
//     /// used to load and display web-content.
//     ///
//     /// AppCore automatically manages focus, keyboard/mouse input, and GPU painting for each active
//     /// overlay. Destroying the overlay will remove it from the window.
//     ///
//     overlay_ = Overlay::Create(window_, window_->width(), window_->height(), 0, 0);

//     ///
//     /// Load a local HTML file into our overlay's View
//     ///
//     overlay_->view()->LoadURL("file:///page.html");

//     ///
//     /// Register our MyApp instance as a WindowListener so we can handle the Window's OnClose event
//     /// below.
//     ///
//     window_->set_listener(this);

//     ///
//     /// Register our MyApp instance as a ViewListener so we can handle the View's OnChangeCursor
//     /// event below.
//     ///
//     overlay_->view()->set_view_listener(this);
//   }

//   virtual ~MyApp() {
//   }

//   ///
//   /// Inherited from WindowListener, called when the Window is closed.
//   ///
//   /// We exit the application when the window is closed.
//   ///
//   virtual void OnClose(ultralight::Window *window) override {
//     app_->Quit();
//   }

//   ///
//   /// Inherited from WindowListener, called when the Window is resized.
//   ///
//   /// (Not used in this sample)
//   ///
//   virtual void OnResize(ultralight::Window *window, uint32_t width, uint32_t height) override {
//   }

//   ///
//   /// Inherited from ViewListener, called when the Cursor changes.
//   ///
//   virtual void OnChangeCursor(ultralight::View *caller, ultralight::Cursor cursor) override {
//     window_->SetCursor(cursor);
//   }

//   void Run() {
//     app_->Run();
//   }
// };

// int main(int argc, char *args[]) {

//   // SDL_Init(SDL_INIT_EVERYTHING);

//   // Window window = Window("cGAY", 400, 400);

//   // Renderer renderer = Renderer(&window);

//   // Resources resources = Resources(&renderer);
//   // resources.loadTexture("monkey.bmp");

//   // while (true) {
//   //   window.eventHandler();
//   //   renderer.clear();
//   //   renderer.drawTexture(resources.getTextureByPath("monkey.bmp"), rand() % 200, rand() % 200);
//   //   renderer.update();

//   //   SDL_Delay(16);
//   // }

//   // SDL_Quit();
//   MyApp app;

//   app.Run();

//   return 0;
// }

#include <AppCore/Platform.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <Ultralight/Ultralight.h>
#include <exception>

namespace UL = ultralight;

UL::RefPtr<UL::Renderer> ULRenderer;

Window *window;

Renderer *renderer;

Resources *resources;

void CreateRenderer() {
  ///
  /// Create our Renderer (call this only once per application).
  ///
  /// The Renderer singleton maintains the lifetime of the library
  /// and is required before creating any Views.
  ///
  /// You should set up the Platform handlers before this.
  ///
  ULRenderer = UL::Renderer::Create();
}

UL::RefPtr<UL::View> view;

void CreateView() {
  ///
  /// Configure our View, make sure it uses the CPU renderer by
  /// disabling acceleration.
  ///
  UL::ViewConfig view_config;
  view_config.is_accelerated = false;

  ///
  /// Create an HTML view, 500 by 500 pixels large.
  ///
  view = ULRenderer->CreateView(500, 500, view_config, nullptr);

  ///
  /// Load a raw string of HTML asynchronously into the View.
  ///
  view->LoadHTML("<h1>Hello World!</h1>");
}

void InitPlatform() {
  ///
  /// Use the OS's native font loader
  ///
  UL::Platform::instance().set_font_loader(UL::GetPlatformFontLoader());

  ///
  /// Use the OS's native file loader, with a base directory of "."
  /// All file:/// URLs will load relative to this base directory.
  ///
  UL::Platform::instance().set_file_system(UL::GetPlatformFileSystem("."));

  ///
  /// Use the default logger (writes to a log file)
  ///
  UL::Platform::instance().set_logger(UL::GetDefaultLogger("ultralight.log"));
}

void Init() {
  UL::Config config;

  ///
  /// Let's set some custom global CSS to make our background
  /// purple by default.
  ///
  config.user_stylesheet = "body { background: purple; }";

  ///
  /// Pass our configuration to the Platform singleton so that
  /// the library can use it.
  ///
  UL::Platform::instance().set_config(config);
}

SDL_Texture *CopyBitmapToTexture(UL::RefPtr<UL::Bitmap> bitmap) {
  ///
  /// Lock the Bitmap to retrieve the raw pixels.
  /// The format is BGRA, 8-bpp, premultiplied alpha.
  ///
  void *pixels = bitmap->LockPixels();

  ///
  /// Get the bitmap dimensions.
  ///
  uint32_t width = bitmap->width();
  uint32_t height = bitmap->height();
  uint32_t stride = bitmap->row_bytes();

  ///
  /// Psuedo-code to upload our pixels to a GPU texture.
  /// << ((int *)pixels)[0]
  // std::cout << width << " " << height << " " << stride << "";

  SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 1, 1, 255, 255, 255, 255);
  // SDL_SaveBMP(surface, "cringe.bmp");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer->renderer, surface);

  SDL_FreeSurface(surface);
  // CopyPixelsToTexture(pixels, width, height, stride);

  ///
  /// Unlock the Bitmap when we are done.
  ///
  bitmap->UnlockPixels();
  return texture;
}

void UpdateLogic() {
  ///
  /// Give the library a chance to handle any pending tasks and timers.
  ///
  ///
  ULRenderer->Update();
}

SDL_Texture *texture;

void RenderOneFrame() {
  ///
  /// Render all active Views (this updates the Surface for each View).
  ///
  ULRenderer->Render();

  ///
  /// Psuedo-code to loop through all active Views.
  ///
  ///
  /// Get the Surface as a BitmapSurface (the default implementation).
  ///
  UL::BitmapSurface *surface = (UL::BitmapSurface *)(view->surface());
  ///
  /// Check if our Surface is dirty (pixels have changed).
  ///
  // std::cout << 2;

  if (!surface->dirty_bounds().IsEmpty()) {
    // std::cout << 1;
    ///
    /// Psuedo-code to upload Surface's bitmap to GPU texture.
    ///

    texture = CopyBitmapToTexture(surface->bitmap());

    // SDL_DestroyTexture(texture);
    ///
    /// Clear the dirty bounds.
    ///
    surface->ClearDirtyBounds();
  }

  renderer->drawTexture(texture, 100, 100);
}

int main() {
  Init();
  InitPlatform();
  CreateRenderer();
  CreateView();

  SDL_Init(SDL_INIT_EVERYTHING);

  window = new Window("cGAY", 400, 400);
  renderer = new Renderer(window);
  resources = new Resources(renderer);

  // resources->loadTexture("monkey.bmp");

  while (true) {
    window->eventHandler();
    renderer->clear();
    // renderer->drawTexture(resources->getTextureByPath("monkey.bmp"), rand() % 200, rand() % 200);
    UpdateLogic();
    RenderOneFrame();
    renderer->update();

    SDL_Delay(100);
  }

  delete window;
  delete renderer;
  delete resources;

  SDL_Quit();

  return 0;
}
