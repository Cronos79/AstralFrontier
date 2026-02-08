# Core Faction Relations Matrix

This document defines the **default diplomatic stance** between the 8 core factions at universe start.
Values are qualitative and intended to seed the simulation; all relations evolve dynamically over time.

Legend:
- **Allied** – Strong cooperation, shared interests
- **Friendly** – Positive relations, trade and diplomacy favored
- **Neutral** – Pragmatic coexistence
- **Tense** – Distrust, frequent friction
- **Hostile** – Open rivalry or proxy conflict
- **Enemy** – Active or near-active warfare

---

## Core Factions
1. Humans (Sol)
2. Aurelian Concord
3. Veyran Syndic Union
4. Khar Dominion
5. Synod of Ithari
6. Heliox Continuum
7. Nomari Free Clans
8. Noctyr Veiled Directorate

---

## Relations Matrix

| From \ To | Humans | Aurelian | Veyran | Khar | Ithari | Heliox | Nomari | Noctyr |
|---------|--------|----------|--------|------|--------|--------|--------|--------|
| **Humans** | — | Tense | Friendly | Hostile | Neutral | Neutral | Friendly | Tense |
| **Aurelian** | Tense | — | Neutral | Enemy | Tense | Tense | Neutral | Hostile |
| **Veyran** | Friendly | Neutral | — | Tense | Tense | Friendly | Allied | Tense |
| **Khar** | Hostile | Enemy | Tense | — | Hostile | Tense | Hostile | Neutral |
| **Ithari** | Neutral | Tense | Tense | Hostile | — | Tense | Neutral | Hostile |
| **Heliox** | Neutral | Tense | Friendly | Tense | Tense | — | Neutral | Tense |
| **Nomari** | Friendly | Neutral | Allied | Hostile | Neutral | Neutral | — | Tense |
| **Noctyr** | Tense | Hostile | Tense | Neutral | Hostile | Tense | Tense | — |

---

## Key Design Notes

### Humans
- Maintain strong trade ties with Veyran and Nomari
- Long-standing hostility with Khar
- Distrust Noctyr intelligence operations

### Aurelian Concord
- Historic enemy of Khar Dominion
- Distrust covert and manipulative powers
- Respect strength over diplomacy

### Veyran Syndic Union
- Allied with Nomari due to trade mobility
- Prefer stable powers and predictable systems
- Avoid direct wars

### Khar Dominion
- Hostile toward most neighbors
- Expansion pressure creates constant conflict
- Neutral stance toward Noctyr due to indirect usefulness

### Synod of Ithari
- Ideological opposition to Khar and Noctyr
- Tension with secular and corporate powers
- Neutral toward Nomari

### Heliox Continuum
- Evaluates others pragmatically
- Friendly toward efficiency-driven Veyran systems
- Distrusts irrational or destabilizing actors

### Nomari Free Clans
- Allied with Veyran
- Avoid ideological or territorial entanglements
- Tolerant but cautious with all powers

### Noctyr Veiled Directorate
- Distrusted universally
- Operates through manipulation and secrecy
- Maintains neutrality where exposure risk is high

---

## Simulation Use
- This matrix seeds **initial diplomatic weights**
- AI systems modify values based on:
  - trade volume
  - border pressure
  - proxy conflicts
  - espionage exposure
  - player intervention

This document should be considered **versioned** and may evolve as balance changes.
