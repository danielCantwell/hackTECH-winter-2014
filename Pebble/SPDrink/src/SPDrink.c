  #include <pebble.h>

static Window *mainWindow;
static Window *statsWindow;
static InverterLayer *inverter_display_layer;
static TextLayer *top_banner_layer;
static Layer *drink_display_layer;
static Layer *drink_badge_layer;
static TextLayer *count_layer;
static TextLayer *stats_layer;
static int dranks = 0;
static int maxDranks = 10;
static char buf[] = "123456";



static void statsWindow_load(Window *mainWindow) {
  Layer *window_layer = window_get_root_layer(statsWindow);
  GRect bounds = layer_get_bounds(window_layer);
  
  //sets up drink number text tag
  stats_layer = text_layer_create((GRect) { .origin = { 50, 60 }, .size = { bounds.size.w-100, 22 } });
  text_layer_set_background_color(stats_layer, GColorClear);
  text_layer_set_text(stats_layer, "test?");
  text_layer_set_font(stats_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  text_layer_set_text_alignment(stats_layer, GTextAlignmentCenter);
  layer_add_child(window_layer,text_layer_get_layer(stats_layer));
  
}

static void statsWindow_unload(Window *mainWindow) {
	text_layer_destroy(stats_layer);
}

//handles up button events
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (dranks <20){
  dranks += 1;
  snprintf(buf,sizeof(buf),"%d",dranks); //prints dranks int as string
  text_layer_set_text(count_layer, buf);
  }
  else {}
}

//handles down button events
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (dranks >0){
  	dranks -= 1;
  	snprintf(buf,sizeof(buf),"%d",dranks);
 	  text_layer_set_text(count_layer, buf);
  }
  else {}
}

//handles select button events
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(count_layer, "Select");
  if (window_stack_get_top_window() == mainWindow){
	  window_set_fullscreen(statsWindow,true);
	  window_stack_push(statsWindow,true);
  }
}

// sets up all button listeners through subscriptionsdaf
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}



//animates the drink level as beverages get counted
static void drink_display_layer_update_callback(Layer *layer, GContext* ctx) {
	Layer *window_layer = window_get_root_layer(mainWindow);
	GRect bounds = layer_get_bounds(window_layer);
	int drinkOriginY = 40;
	int drinkOriginX = 30;
	int drinkWidth = bounds.size.w - 2*drinkOriginX;
	int drinkHeight = bounds.size.h - drinkOriginY - 10;
	GRect drinkRect = GRect(drinkOriginX,drinkOriginY,drinkWidth,drinkHeight);
	graphics_draw_round_rect(ctx, drinkRect,4);
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
	
	//draw white number badge background
	graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx,GPoint(71,73),13);
}


// called when mainWindow is loaded
static void window_load(Window *mainWindow) {
  Layer *window_layer = window_get_root_layer(mainWindow);
  GRect bounds = layer_get_bounds(window_layer);
  
  //sets up drink number text tag
  count_layer = text_layer_create((GRect) { .origin = { 50, 60 }, .size = { bounds.size.w-100, 21 } });
  text_layer_set_background_color(count_layer, GColorClear);
  text_layer_set_text(count_layer, "0");
  text_layer_set_font(count_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  text_layer_set_text_alignment(count_layer, GTextAlignmentCenter);
  
  // sets up the white badge for drink number
//  drink_badge_layer = layer_create(bounds);
//  layer_set_update_proc(drink_badge_layer, drink_badge_layer_update_callback);
  
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
  
  // adds all the layers as children to mainWindow
  layer_add_child(window_layer, text_layer_get_layer(top_banner_layer));
  layer_add_child(window_layer, drink_display_layer);
//  layer_add_child(window_layer, drink_badge_layer);
  layer_add_child(window_layer, text_layer_get_layer(count_layer));
 }

//destroys the layers when app is closed
static void window_unload(Window *mainWindow) {
  text_layer_destroy(count_layer);
  text_layer_destroy(top_banner_layer);
  inverter_layer_destroy(inverter_display_layer);
  layer_destroy(drink_display_layer);
}


static void init(void) {
  mainWindow = window_create();
  window_set_click_config_provider(mainWindow, click_config_provider);
  window_set_window_handlers(mainWindow, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_set_fullscreen(mainWindow,true);
  window_stack_push(mainWindow,true);
  
  statsWindow = window_create();
  window_set_click_config_provider(statsWindow, click_config_provider);
  window_set_window_handlers(statsWindow, (WindowHandlers) {
    .load = statsWindow_load,
    .unload = statsWindow_unload,
  });
  //const bool animated = true;
  
  
  
}

static void deinit(void) {
  window_destroy(mainWindow);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed mainWindow: %p", mainWindow);

  app_event_loop();
  deinit();
}
