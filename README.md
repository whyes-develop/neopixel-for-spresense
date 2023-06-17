# neopixel-for-spresense
Adafruit NeoPixel library for SPRESENSE SDK

## Install
1. Build the Spresense SDK development environment according to the [tutorial](https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html).
2. Clone this repository in the `spresense/externals` directory.
3. Execute the following command in the `spresense/sdk` directory.
   ```
   tools/mkdefconfig.py -d ../externals/neopixel-for-spresense neopixel
   ```
4. Include `neopixel.h` in any application.
## API
See [neopixel.h](/neopixel_extlib/neopixel.h).

## Samples
See [neopixel-for-spresense-samples](https://github.com/whyes-develop/neopixel-for-spresense-samples)

## License
MIT license (See [LICENSE](/LICENSE) for details.)

## Copyright
Copyright(c) 2023 whyes-develop

To implement this library, the following libraries were extremely reference.
Here we express our utmost gratitude.
- [hideakitai/SpresenseNeoPixel](https://github.com/hideakitai/SpresenseNeoPixel) (MIT license, Copyright (c) 2019 Hideaki Tai)
- [KotaMeiwa/nepils](https://github.com/hKotaMeiwa/nepils) (MIT license, Copyright (c) 2023 Kota Meiwa)

Some implementations of these libraries are referenced either explicitly or implicitly in the APIs below.
- neopixel_inizialize()
- neopixel_set()
- neopixel_show()
