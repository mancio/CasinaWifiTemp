# Shopping list - low-power conversion

See the "Known issues / what to fix" and "Target wiring" sections of the main
[README](../README.md) for the reasoning. The battery voltage divider (R1 60k,
R2 10k) is already on the board and stays as is.

| Ref | Part | Price |
|---|---|---|
| U1 | [Pololu S7V8F3 buck-boost module, 3.3 V out, 2.7-11.8 V in, 1 A](https://allegro.pl/oferta/modul-przetwornicy-napiecia-step-up-step-down-3-3v-s7v8f3-17529404843) (also [TME POLOLU-2122](https://www.tme.eu/pl/details/pololu-2122/przetwornice/pololu/)) | ~41 zł |
| C1 | 100 µF / 16 V electrolytic, 105 °C, THT - on U1 `VIN`/`GND`, mind the polarity | ~1,73 zł |
