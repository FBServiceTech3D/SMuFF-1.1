// Moved display pins configuration into separate header files
#if defined(USE_CREALITY_DISPLAY)
#include "DSP_Creality.h"
#if defined(__BRD_SKR_MINI)
#include "../Display/Creality_SPI2.h"
#else
#include "../Display/Creality.h"
#endif
#elif defined(USE_TWI_DISPLAY)
#include "DSP_TWILeonerd.h"
#include "../Display/TWI.h"
#elif defined(USE_LEONERD_DISPLAY)
#include "DSP_TWILeonerd.h"
#include "../Display/Leonerd.h"
#elif defined(USE_MINI12864_PANEL_V21) || defined(USE_MINI12864_PANEL_V20)
#include "DSP_Minipanel.h"
#if defined(__BRD_SKR_MINI)
#include "../Display/Minipanel_SPI2.h"
#else
#include "../Display/Minipanel.h"
#endif
#elif defined(USE_SERIAL_DISPLAY)
#include "DSP_Serial.h"
#include "../Display/SerialDisplay.h"
#else
#include "DSP_Default.h"
#if defined(__BRD_SKR_MINI)
#include "../Display/Default_SPI2.h"
#else
#include "../Display/Default.h"
#endif
#endif
