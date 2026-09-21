"""Regenerates the wiring diagram in photos/ from this description of the circuit."""

from pathlib import Path

import schemdraw
import schemdraw.elements as elm

OUT_DIR = Path(__file__).resolve().parent.parent / "photos"

TOP = 10.0
GND = 0.0
DIV_X = 4.5
BUCK_X = 7.0
MCU_X = 17.0
SENSOR_X = 28.0


def build() -> schemdraw.Drawing:
    d = schemdraw.Drawing(show=False)
    d.config(unit=2.0, fontsize=12)

    # --- Battery ------------------------------------------------------------
    d += elm.Line().at((0, GND)).to((0, 3.5))
    d += elm.Battery().at((0, 3.5)).up().length(3).label("BT1\n4x AA\n4.0-6.4 V", loc="left")
    d += elm.Line().at((0, 6.5)).to((0, TOP))

    # --- Switch on the positive rail ---------------------------------------
    d += elm.Line().at((0, TOP)).to((1.0, TOP))
    d += elm.Switch().at((1.0, TOP)).right().length(2).label(
        "SW1\nopen before\nplugging USB", loc="top"
    )
    d += elm.Line().at((3.0, TOP)).to((BUCK_X, TOP))
    d += elm.Dot().at((DIV_X, TOP))

    # --- Buck-boost converter ----------------------------------------------
    buck = elm.Ic(
        pins=[
            elm.IcPin(name="VIN", side="left", slot="2/2"),
            elm.IcPin(name="GND", side="left", slot="1/2"),
            elm.IcPin(name="VOUT", side="right", slot="2/2"),
        ],
        size=(5.0, 4.0),
        label="U1\nPololu S7V8F3\nbuck-boost 3.3 V",
    ).right().at((BUCK_X, TOP)).anchor("VIN")
    d += buck
    d += elm.Line().at(buck.GND).to((buck.GND.x - 1.0, buck.GND.y))
    d += elm.Line().at((buck.GND.x - 1.0, buck.GND.y)).to((buck.GND.x - 1.0, GND))

    # --- NodeMCU ------------------------------------------------------------
    mcu = elm.Ic(
        pins=[
            elm.IcPin(name="3V3", side="left", slot="4/4"),
            elm.IcPin(name="VIN  (NC)", side="left", slot="3/4"),
            elm.IcPin(name="A0", side="left", slot="2/4"),
            elm.IcPin(name="GND", side="left", slot="1/4"),
            elm.IcPin(name="D0", side="right", slot="4/4"),
            elm.IcPin(name="RST", side="right", slot="3/4"),
            elm.IcPin(name="D2", side="right", slot="1/4"),
        ],
        size=(6.0, 9.0),
        label="U2\nNodeMCU V3\n(ESP8266)\nunmodified",
    ).right().at((MCU_X, TOP)).anchor("3V3")
    d += mcu
    d += elm.Line().at(buck.VOUT).to((MCU_X, TOP))

    # --- Bulk capacitance on the 3V3 rail -----------------------------------
    for x, cap_label in ((13.0, "C1\n1000 µF\nlow ESR"), (15.0, "C2\n100 nF")):
        d += elm.Dot().at((x, TOP))
        d += elm.Capacitor2().at((x, TOP)).down().length(2).label(cap_label, loc="right", ofst=0.15)
        d += elm.Line().at((x, TOP - 2)).to((x, GND))

    # --- Battery voltage divider to A0 --------------------------------------
    a0 = mcu.A0
    d += elm.Resistor().at((DIV_X, TOP)).down().length(2.5).label("R1\n60k", loc="left")
    d += elm.Line().at((DIV_X, TOP - 2.5)).to((DIV_X, a0.y))
    tap = (DIV_X, a0.y)
    d += elm.Dot().at(tap)
    d += elm.Resistor().at(tap).down().length(2.5).label("R2\n10k", loc="left")
    d += elm.Line().at((DIV_X, a0.y - 2.5)).to((DIV_X, GND))
    d += elm.Line().at(tap).to(a0)

    # --- Ground rail --------------------------------------------------------
    d += elm.Line().at((0, GND)).to((SENSOR_X + 1.0, GND))
    d += elm.Line().at(mcu.GND).to((mcu.GND.x - 1.2, mcu.GND.y))
    d += elm.Line().at((mcu.GND.x - 1.2, mcu.GND.y)).to((mcu.GND.x - 1.2, GND))
    d += elm.Ground().at((9.5, GND)).down()

    # --- D0 to RST jumper (deep sleep wake) ---------------------------------
    jumper_x = mcu.D0.x + 1.5
    d += elm.Line().at(mcu.D0).to((jumper_x, mcu.D0.y))
    d += elm.Line().at((jumper_x, mcu.D0.y)).to((jumper_x, mcu.RST.y))
    d += elm.Line().at((jumper_x, mcu.RST.y)).to(mcu.RST)
    d += elm.Annotate().at((jumper_x, (mcu.D0.y + mcu.RST.y) / 2)).delta(dx=2.2, dy=1.8).label(
        "D0-RST: deep sleep wake", color="gray"
    )

    # --- DS18B20 ------------------------------------------------------------
    sensor = elm.Ic(
        pins=[
            elm.IcPin(name="VCC", side="left", slot="3/3"),
            elm.IcPin(name="DQ", side="left", slot="2/3"),
            elm.IcPin(name="GND", side="left", slot="1/3"),
        ],
        size=(4.0, 4.0),
        label="U3\nDS18B20\nmodule\n(4k7 on board)",
    ).right().at((SENSOR_X, TOP - 2.0)).anchor("VCC")
    d += sensor

    feed_x = 14.0
    d += elm.Dot().at((feed_x, TOP))
    d += elm.Line().at((feed_x, TOP)).to((feed_x, TOP + 2.5))
    d += elm.Line().at((feed_x, TOP + 2.5)).to((SENSOR_X - 2.0, TOP + 2.5))
    d += elm.Line().at((SENSOR_X - 2.0, TOP + 2.5)).to((SENSOR_X - 2.0, sensor.VCC.y))
    d += elm.Line().at((SENSOR_X - 2.0, sensor.VCC.y)).to(sensor.VCC)

    d += elm.Line().at(mcu.D2).to((SENSOR_X - 3.5, mcu.D2.y))
    d += elm.Line().at((SENSOR_X - 3.5, mcu.D2.y)).to((SENSOR_X - 3.5, sensor.DQ.y))
    d += elm.Line().at((SENSOR_X - 3.5, sensor.DQ.y)).to(sensor.DQ)

    d += elm.Line().at(sensor.GND).to((SENSOR_X - 1.0, sensor.GND.y))
    d += elm.Line().at((SENSOR_X - 1.0, sensor.GND.y)).to((SENSOR_X - 1.0, GND))

    return d


def main() -> None:
    OUT_DIR.mkdir(exist_ok=True)
    drawing = build()
    drawing.save(str(OUT_DIR / "wiring-diagram.svg"))
    drawing.save(str(OUT_DIR / "wiring-diagram.png"), dpi=200)
    print(f"written to {OUT_DIR}")


if __name__ == "__main__":
    main()
