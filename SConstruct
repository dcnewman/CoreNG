import os
import sys
from os.path import join, expanduser, isfile

platform = ARGUMENTS.get('platform', 'duet').lower()

target_name       = 'libCoreNG'
scons_variant_dir = 'SAM3X8E'

if (platform == 'duet') or (platform == 'sam3x8e'):
   platform          = 'sam3x8e'
   scons_variant_dir = 'SAM3X8E'
   mcpu              = 'cortex-m3'
elif (platform == 'ng') or (platform == 'sam4e8e'):
   platform          = 'sam4e8e'
   scons_variant_dir = 'SAM4E8E'
   mcpu              = 'cortex-m4'
else:
   raise Exception('Unrecognized platform ' + platform)

# Generate a directory tree of the directories in the list dir
# excluding any directory (and children) from the list ignore

def list_dirs(dir, ignore):
  list = []
  for d in dir:
    subdirs = [ d + '/' + name for name in os.listdir(d) if os.path.isdir(os.path.join(d, name)) and \
    (name[0] != '.') and (not (d + '/' + name) in ignore) ]
    list += list_dirs(subdirs, ignore)
  return dir + list


##########
#
# Load data from ~/.rrf_arduino_paths.py

tmp_dict = {  }
home = expanduser('~')
if home[-1] != '/':
    home += '/'
    
site_file = home + '.rrf_arduino_paths.py'
if isfile(site_file):
    with open(site_file) as f:
        exec(f.read(), tmp_dict)
    keys_of_interest = [ 'gccarm_bin' ]
    for key in keys_of_interest:
        if key in tmp_dict:
            if type(tmp_dict[key]) is str:
                exec(key + '="' + tmp_dict[key] + '"')
            elif type(tmp_dict[key]) is int:
                exec(key + '=' + str(tmp_dict[key]))
            else:
                raise Exception(key + ' in ' + site_file + ' is of an ' + \
                        'unsupported type')

have_bin = 'gccarm_bin' in globals()

if not have_bin:
  raise Exception('You must first create the file ' + site_file + \
      ' before building.  See ' + \
      '~/sample_rrf_arduino_paths.py for an example.')

os.environ['GCCARM_BIN'] = gccarm_bin

###########
#
# The source directories we will be building
#
core_dirs = [
    'cores',
    'libraries',
    'variants',
    'asf' ]

############
#
# Source directories to ignore
if platform == 'sam3x8e':
    ignore_dirs = [
      'asf/common/services/storage/ecc_hamming',
      'asf/sam/utils/syscalls/gcc',
      'asf/common/services/spi',
      'variants/duetNG',
      'asf/common/components/memory/sd_mmc/sd_mmc_spi.h',
      'asf/common/components/memory/sd_mmc/sd_mmc_spi.c',
      'asf/common/components/memory/sd_mmc/module_config_spi',
      'asf/common/utils/osprintf',
      'asf/common/utils/membag',
      'asf/common/utils/stdio',
      'asf/common/services/clock/sam4s',
      'asf/common/services/clock/sam3s',
      'asf/common/services/clock/sam4e',
      'asf/sam/components/ethernet_phy',
      'asf/sam/components/ethernet_phy/ksz8061rnb',
      'asf/sam/components/ethernet_phy/ksz8081mnx',
      'asf/sam/components/ethernet_phy/ksz8081rna',
      'asf/sam/components/ethernet_phy/ksz8851snl',
      'asf/sam/components/ethernet_phy/dm9161a',
      'asf/sam/drivers/acc',
      'asf/sam/drivers/aes',
      'asf/sam/drivers/crccu',
      'asf/sam/drivers/afec',
      'asf/sam/drivers/udp',
      'asf/sam/drivers/xdmac',
      'asf/sam/drivers/abdacb',
      'asf/common/services/delay',
      'asf/common/services/serial',
      'asf/common/services/fifo',
      'asf/common/services/crc32',
      'asf/common/services/isp',
      'asf/common/services/gfx_mono',
      'asf/common/services/gfx',
      'asf/common/services/sensors',
      'asf/common/services/hugemem',
      'asf/common/services/freertos',
      'asf/common/services/calendar',
      'asf/common/services/adp',
      'asf/common/services/usb/class/phdc',
      'asf/common/services/usb/class/msc',
      'asf/common/services/usb/class/hid',
      'asf/common/services/usb/class/dfu_flip',
      'asf/common/services/usb/class/composite',
      'asf/common/services/usb/class/aoa',
      'asf/common/drivers',
      'libraries/HID',
      'libraries/SPI',
      'asf/sam/utils/cmsis/samg',
      'asf/sam/utils/cmsis/same70',
      'asf/sam/utils/cmsis/sam4s',
      'asf/sam/utils/cmsis/sam4n',
      'asf/sam/utils/cmsis/sam4l',
      'asf/sam/utils/cmsis/sam4e',
      'asf/sam/utils/cmsis/sam4cp',
      'asf/sam/utils/cmsis/sam4cm32',
      'asf/sam/utils/cmsis/sams70',
      'asf/sam/utils/cmsis/samv70',
      'asf/sam/utils/cmsis/samv71',
      'asf/sam/utils/cmsis/sam4cm',
      'asf/sam/utils/cmsis/sam4c',
      'asf/sam/utils/cmsis/sam3u',
      'asf/sam/utils/cmsis/sam3s8',
      'asf/sam/utils/cmsis/sam3s',
      'asf/sam/utils/cmsis/sam3n',
      'asf/thirdparty/CMSIS/DSP_Lib',
      'asf/common/applications',
      'asf/sam/applications',
      'system/CMSIS/Device/ARM/ARMCM3/Source/Templates',
      'system/CMSIS/CMSIS/DSP_Lib',
      'system/CMSIS/Device/ARM/ARMCM4',
      'system/CMSIS/Device/ARM/ARMCM0',
      'system/CMSIS/Device/ATMEL/sam3sd8',
      'system/CMSIS/Device/ATMEL/sam3u',
      'system/CMSIS/Device/ATMEL/sam3s',
      'system/CMSIS/Device/ATMEL/sam3n',
      'system/CMSIS/Device/ATMEL/sam4s' ]
else:
    ignore_dirs = [
      'asf/common/services/spi',
      'asf/common/drivers/nvm',
      'asf/common/services/clock/sam3s',
      'asf/common/services/clock/sam3x',
      'asf/common/services/clock/sam4s',
      'asf/common/services/usb/class/composite',
      'asf/common/services/usb/class/dfu_flip',
      'asf/common/services/usb/class/hid',
      'asf/common/services/usb/class/msc',
      'asf/common/services/usb/class/phdc',
      'asf/common/services/usb/class/aoa',
      'asf/common/services/serial',
      'asf/common/services/delay',
      'asf/common/services/fifo',
      'asf/common/services/crc32',
      'asf/common/services/adp',
      'asf/common/utils/stdio',
      'asf/common/utils/osprintf',
      'asf/common/utils/membag',
      'asf/sam/components/ethernet_phy',
      'asf/sam/drivers/acc',
      'asf/sam/drivers/aes',
      'asf/sam/drivers/crccu',
      'asf/sam/drivers/adc',
      'asf/sam/drivers/emac',
      'asf/sam/drivers/trng',
      'asf/sam/drivers/uotghs',
      'asf/sam/drivers/xdmac',
      'asf/sam/utils/cmsis/samv70',
      'asf/sam/utils/cmsis/sams70',
      'asf/sam/utils/cmsis/same70',
      'asf/sam/utils/cmsis/sam4s',
      'asf/sam/utils/cmsis/sam4n',
      'asf/sam/utils/cmsis/sam4l',
      'asf/sam/utils/cmsis/sam4cp',
      'asf/sam/utils/cmsis/sam4cm32',
      'asf/sam/utils/cmsis/sam4cm',
      'asf/sam/utils/cmsis/samv71',
      'asf/sam/utils/cmsis/sam4c',
      'asf/sam/utils/cmsis/sam3x',
      'asf/sam/utils/cmsis/sam3u',
      'asf/sam/utils/cmsis/sam3s8',
      'asf/sam/utils/cmsis/sam3s',
      'asf/sam/utils/cmsis/sam3n',
      'libraries/SPI',
      'libraries/HID',
      'variants/duet' ]

##########
#
# Include file directories
#
if platform == 'sam3x8e':
  include_paths = [
    'cores/arduino',
    'asf',
    'asf/sam/utils',
    'asf/sam/utils/header_files',
    'asf/sam/utils/preprocessor',
    'asf/sam/utils/cmsis/sam3x/include',
    'asf/sam/drivers',
    'asf/sam/drivers/dmac',
    'asf/sam/drivers/efc',
    'asf/sam/drivers/hsmci',
    'asf/sam/drivers/pio',
    'asf/sam/drivers/pmc',
    'asf/sam/drivers/spi',
    'asf/sam/drivers/usart',
    'asf/common/utils',
    'asf/common/services/clock',
    'asf/common/services/ioport',
    'asf/common/services/sleepmgr',
    'asf/common/services/usb',
    'asf/common/services/usb/udc',
    'asf/common/services/usb/class/cdc',
    'asf/common/services/usb/class/cdc/device',
    'asf/thirdparty/CMSIS/Include',
    'variants/duet' ]
else:
  include_paths = [
    'cores/arduino',
    'asf',
    'asf/sam/utils',
    'asf/sam/utils/header_files',
    'asf/sam/utils/preprocessor',
    'asf/sam/utils/cmsis/sam4e/include',
    'asf/sam/drivers',
    'asf/sam/drivers/dmac',
    'asf/sam/drivers/efc',
    'asf/sam/drivers/hsmci',
    'asf/sam/drivers/pio',
    'asf/sam/drivers/pmc',
    'asf/sam/drivers/spi',
    'asf/sam/drivers/usart',
    'asf/common/utils',
    'asf/common/services/clock',
    'asf/common/services/ioport',
    'asf/common/services/sleepmgr',
    'asf/common/services/usb',
    'asf/common/services/usb/udc',
    'asf/common/services/usb/class/cdc',
    'asf/common/services/usb/class/cdc/device',
    'asf/thirdparty/CMSIS/Include',
    'variants/duetNG' ]


##########
#
# Build a scons environment

VariantDir(scons_variant_dir, './', 'duplicate=0')

# Make the clean command remove the variant sources
clean_dirs = [ join(scons_variant_dir, i) for i in core_dirs ]
Clean('.', clean_dirs)

env=Environment( tools = ['default', 'ar', 'g++', 'gcc'],
   CPPPATH = include_paths,
   LIBPATH = ['.'] )

# Compiler flags shared by C and C++
if platform == 'sam3x8e':
  env.Replace( CCFLAGS = [
      '-c',
      '-ffunction-sections',
      '-fdata-sections', 
      '--param', 'max-inline-insns-single=500',
      '-nostdlib',
      '-Wall',
      '-mthumb',
      '-mcpu=' + mcpu,
      '-Dprintf=iprintf',
      '-D__SAM3X8E__',
      '-DF_CPU=84000000L',
      '-DUDD_ENABLE',
      '-DUDD_NO_SLEEP_MGR' ] )
else:
  env.Replace( CCFLAGS = [
      '-c',
      '-ffunction-sections',
      '-fdata-sections',
      '--param', 'max-inline-insns-single=500',
      '-nostdlib',
      '-Wall',
      '-mthumb',
      '-mcpu=' + mcpu,
      '-Dprintf=iprintf',
      '-D__SAM4E8E__',
      '-DF_CPU=120000000L',
      '-DUDD_ENABLE',
      '-DUDD_NO_SLEEP_MGR' ] )

# C compiler flags
env.Replace( CFLAGS = [
    '-O2',
    '-std=gnu99' ] )

# C++ flags
env.Replace( CXXFLAGS = [
    '-fno-threadsafe-statics',
    '-fno-rtti',
    '-fno-exceptions',
    '-O2',
    '-std=gnu++11' ] )

env.SetDefault( GCCARM_BIN = gccarm_bin )

env.Replace( RANLIB = "$GCCARM_BIN/arm-none-eabi-ranlib" )
env.Replace( CC = "$GCCARM_BIN/arm-none-eabi-gcc" )
env.Replace( CXX = "$GCCARM_BIN/arm-none-eabi-g++" )
env.Replace( AR = "$GCCARM_BIN/arm-none-eabi-ar" )
env.Replace( ARFLAGS = "rcs" )
env.Replace( ASFLAGS = "-c -g -x assembler-with-cpp" )
env.Replace( SIZE = "$GCCARM_BIN/arm-none-eabi-size" )
env.Replace( OBJCOPY = "$GCCARM_BIN/arm-none-eabi-objcopy" )
env.Replace( ELF = "$GCCARM_BIN/arm-none-eabi-gcc" )
env.Replace( LD = "$GCCARM_BIN/arm-none-eabi-gcc" )

env.Append( BUILDERS = { 'Elf' : Builder(action='"$GCCARM_BIN/arm-none-eabi-gcc" -Os -Wl,--gc-sections -mcpu=' + mcpu + ' "-Wl,-Map,CoreNG.map"  -o $TARGET $_LIBDIRFLAGS -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--start-group $_LIBFLAGS $SOURCES  -Wl,--end-group -lm -gcc') } )

env.Append( BUILDERS = { 'Hex' : Builder(action='"$GCCARM_BIN/arm-none-eabi-objcopy" -O binary  $SOURCES $TARGET', suffix='.hex', src_suffix='.elf') } )

# Generate the list of source directories to consider
src_dirs = list_dirs(core_dirs, ignore_dirs)

# Generate the list of source files to compile
srcs = []
for dir in src_dirs:
    srcs += \
    env.Glob(join(scons_variant_dir, dir, '*.c')) + \
    env.Glob(join(scons_variant_dir, dir, '*.cpp')) + \
    env.Glob(join(scons_variant_dir, dir, '*.S'))

env.Depends(srcs, join(scons_variant_dir, 'libraries', 'Storage', 'sd_mmc_mem.h'))

# Now generate the target library
objs = env.Object(srcs)
lib = env.Library(join(scons_variant_dir, target_name), objs)
