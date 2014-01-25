#include <pebble.h>

static Window *window;
static Layer *drink_display_layer;
static TextLayer *text_layer;
static int dranks = 0;
static int maxDranks = 10;
static char buf[] = "123456";

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
  //new
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (dranks <10){
  dranks += 1;
  snprintf(buf,sizeof(buf),"%d",dranks);
  text_layer_set_text(text_layer, buf);
  }
  else {
  text_layer_set_text(text_layer,"ALCOHOLIC");
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (dranks >0){
  	dranks -= 1;
  	snprintf(buf,sizeof(buf),"%d",dranks);
 	text_layer_set_text(text_layer, buf);
  }
  else {
	  
	  text_layer_set_text(text_layer, "you should drink more!");
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void drink_display_layer_update_callback(Layer *layer, GContext* ctx) {
	Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    int drinkOriginY = (bounds.size.h-50)/maxDranks*(maxDranks-dranks) + 40;
    int drinkOriginX = 30;
    int drinkWidth = bounds.size.w - 2*drinkOriginX;
    int drinkHeight = bounds.size.h - drinkOriginY - 10;
	GRect drinkRect = GRect(drinkOriginX,drinkOriginY,drinkWidth,drinkHeight);
	graphics_fill_rect(ctx, drinkRect,0,GCornerNone);
	//graphics_draw_line(ctx,GPoint(10,10),GPoint(50,50));
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  
  
  text_layer = text_layer_create((GRect) { .origin = { 0, 60 }, .size = { bounds.size.w, 21 } });
  text_layer_set_text(text_layer, "Begin Drinking");
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  
  drink_display_layer = layer_create(bounds);
  //inverter_layer_init(&drink_display_layer,GRect(0,0,bounds.size.w,bounds.size.h));
  layer_set_update_proc(drink_display_layer, drink_display_layer_update_callback);
  layer_add_child(window_layer, drink_display_layer);
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
  layer_destroy(drink_display_layer);
}

//static void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
//	layer_mark_dirty(drink_display_layer);
//}

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
