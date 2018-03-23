#include <cstddef>
#include <iostream>
#include <zbar.h>
#include <cmath>

void data_handler (zbar::zbar_image_t *img, const void *userdata)
{
    const zbar::zbar_symbol_t *sym = zbar_image_first_symbol(img);
    assert(sym);
    int n = 0;
    for(; sym; sym = zbar_symbol_next(sym)) {
        if(zbar_symbol_get_count(sym))
            continue;
        if(zbar_symbol_get_loc_size(sym) == 4)
        {
            int xs[4], ys[4];
            for (uint i = 0; i < 4; i++)
            {
                xs[i] = zbar_symbol_get_loc_x(sym, i);
                ys[i] = zbar_symbol_get_loc_y(sym, i);
                //std::cout << xs[i] << ", " << ys[i] << "\t";
            }
            std::cout << std::endl;
            std::cout << xs[0]-xs[1] << ", " << ys[0]-ys[1] << std::endl;
            std::cout << atan2(ys[0]-ys[1],xs[0]-xs[1])*180.0/M_PI << std::endl;
        }
        std::cout << zbar_symbol_get_data(sym) <<  std::endl;
        n++;   
    }
}


int processor_method(std::string const &device)
{
    zbar::zbar_processor_t *processor = zbar::zbar_processor_create(1);

    zbar::zbar_processor_set_data_handler(processor, data_handler, nullptr);
    
    if(zbar::zbar_processor_init(processor, device.c_str(), 1))
        return(zbar::zbar_processor_error_spew(processor, 0));

    if(zbar::zbar_processor_set_visible(processor, 1))
        return(zbar::zbar_processor_error_spew(processor, 0));
    
    if(zbar::zbar_processor_set_active(processor, 1))
        return(zbar::zbar_processor_error_spew(processor, 0));
    
    int active = 1;
    int rc;
    while((rc = zbar::zbar_processor_user_wait(processor, -1)) >= 0) {
        if(rc == 'q' || rc == 'Q')
            break;
        if(rc == ' ') {
            active = !active;
            if(zbar::zbar_processor_set_active(processor, active))
                return(zbar::zbar_processor_error_spew(processor, 0));
        }
    }

    /* report any errors that aren't "window closed" */
    if(rc && rc != 'q' && rc != 'Q' &&
       zbar::zbar_processor_get_error_code(processor) != zbar::ZBAR_ERR_CLOSED)
        return(zbar::zbar_processor_error_spew(processor, 0));

    /* free resources (leak check) */
    zbar::zbar_processor_destroy(processor);
}

int scanner_method(std::string const &device)
{
    zbar::ImageScanner scanner;
    
    //scanner.enable_cache(false);
    scanner.set_config(zbar::ZBAR_QRCODE,zbar::ZBAR_CFG_ENABLE,1);
    
    zbar::Video video;
    std::string d = device;
    video.open(d);
    video.enable();
    
    
    while(true)
    {
        zbar::Image image = video.next_image();
        std::cout << image.get_width() << "x" << image.get_height() << std::endl;
        int ret = scanner.scan(image);
        std::cout << ret << std::endl;
        zbar::SymbolSet ss = scanner.get_results();
    }
    
    return 0;
}

int main(int argc, char *argv[])
{   
    std::string device = "/dev/video0";
    if(argc > 1)
        device = argv[1];

    return processor_method(device);
    //return scanner_method(device);
    
}
