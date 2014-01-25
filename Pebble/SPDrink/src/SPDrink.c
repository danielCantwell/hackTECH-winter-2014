#include <pebble.h>

static Window *window;
static InverterLayer *inverter_display_layer;
static TextLayer *top_banner_layer;
static Layer *drink_display_layer;
static Layer *drink_badge_layer;
static TextLayer *text_layer;
static int dranks = 0;
static int maxDranks = 10;
static char buf[] = "123456";

//handles select button events
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Select");
}

//handles up button events
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (dranks <20){
  dranks += 1;
  snprintf(buf,sizeof(buf),"%d",dranks); //prints dranks int as string
  text_layer_set_text(text_layer, buf);
  }
  else {}
}

//handles down button events
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (dranks >0){
  	dranks -= 1;
  	snprintf(buf,sizeof(buf),"%d",dranks);
 	text_layer_set_text(text_layer, buf);
  }
  else {}
}

// sets up all button listeners through subscription
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

//animates the drink level as beverages get counted
static void drink_display_layer_update_callback(Layer *layer, GContext* ctx) {
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);
	
	//if under maxDranks, then image gets updated
    if (dranks<maxDranks){
		int drinkOriginY = (bounds.size.h-50)/maxDranks*(maxDranks-dranks) + 40;
		int drinkOriginX = 30;
		int drinkWidth = bounds.size.w - 2*drinkOriginX;
		int drinkHeight = bounds.size.h - drinkOriginY - 10;
		GRect drinkRect = GRect(drinkOriginX,drinkOriginY,drinkWidth,drinkHeight);
		graphics_fill_rect(ctx, drinkRect,4,GCornersAll);
	}
	// past maxDranks, drinks are counted, but image does not change
	else{
		int drinkOriginY = (bounds.size.h-50)/maxDranks*(maxDranks-maxDranks) + 40;
		int drinkOriginX = 30;
		int drinkWidth = bounds.size.w - 2*drinkOriginX;
		int drinkHeight = bounds.size.h - drinkOriginY - 10;
		GRect drinkRect = GRect(drinkOriginX,drinkOriginY,drinkWidth,drinkHeight);
		graphics_fill_rect(ctx, drinkRect,4,GCornersAll);
	}
}

// creates white badge to go behind drink count
static void drink_badge_layer_update_callback(Layer *layer, GContext* ctx){
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_fill_circle(ctx,GPoint(71,73),13);
}

// called when window is loaded
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  //sets up drink number text tag
  text_layer = text_layer_create((GRect) { .origin = { 50, 60 }, .size = { bounds.size.w-100, 21 } });
  text_layer_set_background_color(text_layer, GColorClear);
  text_layer_set_text(text_layer, "0");
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  
  // sets up the white badge for drink number
  drink_badge_layer = layer_create(bounds);
  layer_set_update_proc(drink_badge_layer, drink_badge_layer_update_callback);
  
  // sets up drink bar
 // inverter_display_layer = inverter_layer_create(GRect(50,60,bounds.size.w-100,21));
  drink_display_layer = layer_create(bounds);
  //inverter_layer_init(&drink_display_layer,GRect(0,0,bounds.size.w,bounds.size.h));
  layer_set_update_proc(drink_display_layer, drink_display_layer_update_callback);
  
  // Sets up a top heading banner
  top_banner_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, 21 } });
  text_layer_set_background_color(top_banner_layer, GColorClear);
  text_layer_set_text(top_banner_layer, "SPDrinks");
  text_layer_set_font(top_banner_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  text_layer_set_text_alignment(top_banner_layer, GTextAlignmentCenter);
  
  // adds all the layers as children to window
  layer_add_child(window_layer, text_layer_get_layer(top_banner_layer));
  layer_add_child(window_layer, drink_display_layer);
  layer_add_child(window_layer, drink_badge_layer);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
 }

//destroys the layers when app is closed
static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
  text_layer_destroy(top_banner_layer);
  inverter_layer_destroy(inverter_display_layer);
  layer_destroy(drink_display_layer);
}


static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  
  window_stack_push(window,true);
  
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
