# Lab Rax Cooling Fan Controller
As Homelab Upgrade 2026 progress, I've gotten to a point
where I want to install a fan in my Lab Rax mini rack.

This turned out to be a bigger adventure than I expected
and throughout the process I collected a bunch of information 
that I will never remember, so I've captured my notes.

While I'm focused on my Lab Rax build this setup should
work in any number of situations

## Components
* ESP 32
* 12v Buck Converter
* DHT22
* 120mm Fan

## Power Budget
Assuming an 85% buck efficiency

| Component | Voltage | Current (Max) | 12V Input Current (Max) |
| --------- | ------- | ----------    | ----------------------- |
| ESP23     | 3.3V    | 0.50 A        | 0.16 A                  |
| Fan       | 12V     | 0.33 A        | 0.33 A                  |
| DHT22     | 3.3 V   | 0.0025 A      | 0.0007 A                |
|           |         |               |                         |
| **Total** |         |               | **0.49 A**              |

## Wiring
### Diagram
```mermaid
flowchart TD
    subgraph ESP32
        esp_33[3.3V]
        esp_gnd[Gnd]
        esp13[GPIO 13]
        esp14[GPIO 14]
    end

    subgraph 12V Power Suppy
        12v+[+]
        12v-[Gnd]
    end

    subgraph DHT22
        dht+[+]
        dht-[Gnd]
        dhtData[Data]
    end

    subgraph buck[Buck Converter]
        buckIn+[+ in]
        buckIn-[Gnd in]
        buckOut+[3.3V + Out]
        buckOut-[Gnd out]
    end

    subgraph Fan
        fan+[+]
        fan-[Gnd]
        fanTach[Tach]
        fanPmw[PMW]
    end

    dhtData <--> esp13

    fanPmw <--> esp14

    12v+ <--> buckIn+
    12v- <--> buckIn-

    fan+ <--> 12v+
    fan- <--> 12v-

    dht+ <--> buckOut+
    dht- <--> buckOut-
    

    esp_33 <--> buckOut+
    esp_gnd <--> buckOut-
```

## Printed Case

## Code
TK

## Notes & Observations
