# AI Strategy Model

This document defines how AI factions **think, plan, and act** in a large persistent universe.
The goal is to balance:
- Server load (AI thinking is expensive)
- Believability (AI must feel alive)
- Timescale (ships/stations take months of game time)
- Reactivity (wars and crises still respond)

AI does not “micro” constantly — it **commits to plans** and executes them over time.

---

## Design Principles
- AI decisions are layered: tactical → operational → strategic
- Strategic decisions happen **infrequently** (to reduce load and add weight)
- Most AI actions are **execution**, not constant re-planning
- Re-planning happens when something important changes (war, collapse, major loss)
- AI should feel busy even when strategy ticks are sparse

---

## Time and Cadence Assumptions (Baseline)
These are tunable constants, shown as a starting point that matches your intent:

- **1 real day ≈ 1 game month**
- Typical build times:
  - Small ships: ~1–7 game days (hours to < 1 real day)
  - Medium ships: ~2–6 game weeks (1–5 real days)
  - Capital ships: ~2–6 game months (2–6 real days)

This makes “2 strategic decisions per real day” feel reasonable: it’s roughly
two “leadership meetings” per game month.

---

## AI Thinking Layers and Frequencies

### 1) Tactical AI (Short Tick)
**Frequency:** seconds (server tick layer)  
**Scope:** only active entities (combat, travel, docking)

Handles:
- Combat tactics
- Target selection
- Formation and retreat logic
- Local threat reactions
- Escort behavior

**Performance rule:** only run when an entity is active or near activity.

---

### 2) Operational AI (Medium Tick)
**Frequency:** every 5–15 real minutes (tunable)  
**Scope:** active systems, trade lanes, production nodes

Handles:
- Convoy scheduling
- Mining allocation
- Station output routing
- Patrol assignments
- Local response to piracy
- Short-term market arbitrage (“restock this port”)

Operational AI creates constant motion without heavy planning.

---

### 3) Strategic AI (Long Tick)
**Frequency:** ~2 times per real day (baseline)  
Example: every 12 real hours

Handles:
- War declarations / ceasefires
- Expansion targets
- Major build programs (stations, shipyards, capitals)
- Diplomatic posture shifts
- Long-term budget allocation
- Gate control strategy and chokepoint priorities

Strategic AI is expensive, so we keep it rare and high-impact.

---

## Event-Driven “Interrupts” (Critical)
Even with sparse strategy ticks, AI must react to shocks.

**Interrupt triggers** cause a faction to re-evaluate early:
- Capital ship destroyed
- Core system threatened
- Trade corridor collapse
- Major rebellion
- Intelligence exposure (Noctyr-style events)
- Bankruptcy / credit crisis
- Enemy massing fleets at border

**Rule:** interrupts do not run full strategy for every event; they schedule a
limited “crisis response” pass that adjusts priorities immediately.

---

## Planning Model: Goals → Plans → Tasks

### Goals (Strategic)
A faction maintains 1–3 active goals, such as:
- Defend core territory
- Expand into a resource-rich frontier
- Control a trade corridor
- Suppress piracy near chokepoints
- Weaken a rival through interdiction
- Fund proxy wars

### Plans (Operational)
Each goal produces plans:
- Build 3 escort fleets
- Construct refinery station in system X
- Interdict route Y for 2 game months
- Sponsor pirates in corridor Z (covert)

### Tasks (Scheduled Events)
Plans are converted into scheduled tasks:
- Ship build queue entries
- Convoy schedules
- Patrol rotations
- Diplomatic offers
- Espionage ops

Tasks execute continuously between strategic ticks.

---

## Budget System (Keeps AI Coherent)
Every strategic tick, a faction allocates budget across categories:

- **Military:** fleets, replacements, defenses
- **Industry:** refineries, factories, shipyards
- **Trade:** convoys, market hubs, route security
- **Security:** patrols, anti-piracy, internal stability
- **Diplomacy:** treaties, bribes, sanctions
- **Intelligence:** spying, sabotage, misinformation

Budgets are influenced by faction personality (from faction docs).

---

## AI Trading Behavior (How often does it trade?)
AI trading should feel frequent, but not “thinking-heavy.”

### Trade Actions Split into Two Types

#### A) Routine Logistics (Operational Layer)
**Frequency:** every medium tick (5–15 minutes real time)  
Examples:
- Refill station fuel
- Move refined plates to shipyard
- Export surplus goods
- Import needed components

This is mostly rule-based and cheap.

#### B) Market Plays (Strategic Layer)
**Frequency:** during strategic ticks (2/day)  
Examples:
- Establish a new trade route
- Shift export focus due to war risk
- Create embargo/sanctions
- Build a trade hub to capitalize on price spread

This is the “thinking” part and runs rarely.

**Result:** the AI trades constantly, but only *re-plans* trade strategy occasionally.

---

## War Behavior (Avoid Twitchy Wars)
War decisions are heavy, so they occur on strategic ticks unless interrupted.

### War Entry Conditions (Examples)
- Border pressure above threshold
- Rare resource need critical
- Rival weakened or distracted
- Trade route threatened
- Ideological hostility (Ithari) or expansion drive (Khar)

### War Execution
Once at war:
- operational AI runs patrols, raids, blockades daily
- strategic AI revisits:
  - “is this war still worth it?”
  - “should we escalate to capitals?”
  - “should we sue for peace?”

Wars should last **months of game time**, not hours.

---

## Construction and Queues
Because builds take months of game time:

- AI issues build orders on strategic ticks
- Shipyards and factories execute continuously
- Losses are filled by replacement policies (operational)
- Capital production is capped by:
  - rare materials
  - dedicated shipyards
  - political risk and visibility

---

## Territory and Policing (Overextension Pressure)
AI must respect the “bigger is harder” rule:

As territory grows, AI increases budget to:
- security
- logistics
- anti-piracy
- stability

If it fails:
- piracy rises
- rebellion risk rises
- trade collapses
- the faction loses frontier holdings

This produces believable rise-and-fall arcs.

---

## Performance Controls (Server Load Safety)
To keep server load stable:

- Only run tactical AI for active entities
- Only run operational AI for:
  - systems with players, stations, routes, or conflict
- Strategic AI:
  - limited to 2/day per core faction (baseline)
  - minor factions may run 1/day or 1/2 days
  - pirates run simpler “growth & raid” logic per medium tick

Optional scaling:
- Stagger faction strategy ticks (not all at same time)
- Prioritize “hot regions” (where players are)
- Use summary AI for dormant areas

---

## Recommended Baseline Schedule
- Tactical: continuous for active entities
- Operational: every 10 minutes real time
- Strategic: every 12 hours real time (≈ 2/game months)

This should feel alive while remaining scalable.

---

## Version Notes
This model is designed to be tuned by:
- Universe size
- Player count
- Hardware
- Desired pacing

If the AI feels dead:
- increase operational actions (cheap), not strategic ticks (expensive).

If the server load spikes:
- reduce dormant-region operational scope first.
