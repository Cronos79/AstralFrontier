# Simulation Tick Model

This document defines how time advances in the universe and how simulation work is distributed.
The goal is to support a **massive, always-running universe** without requiring every system, ship,
and faction to update every server frame.

---

## Core Design Goals
- Scale to a very large universe
- Avoid per-frame simulation of everything
- Keep AI decisions meaningful, not reactive spam
- Present **human-readable game time**
- Allow time acceleration without breaking logic

This is a **time-layered simulation**, not a real-time RTS loop.

---

## Game Time vs Real Time

### Game Calendar
The universe uses a **human-readable calendar**:

- Year
- Month
- Day
- (Optional: hour for events)

Example:
> Year 3025, Month 07, Day 14

Players never see raw tick counts.

---

### Real-Time to Game-Time Mapping
Game time advances based on real time, but not 1:1.

Example baseline:
- **1 real hour = 1.5 game days**
- **1 real day ≈ 1 game month**
- **1 real year ≈ ~12 game years**

This ratio can be tuned globally.

---

### Time Drift Handling
Because server ticks may lag:
- Game time advances using **accumulated real-time deltas**
- Missed ticks do not freeze the universe
- Simulation uses elapsed time, not frame count

The calendar always moves forward smoothly.

---

## Tick Layers Overview

The simulation is split into **three major tick layers**:

1. **Short Tick** – moment-to-moment operations  
2. **Medium Tick** – operational decisions  
3. **Long Tick** – strategic decisions  

Each layer runs at a different frequency.

---

## 1. Short Tick (Tactical Layer)

### Frequency
- Every server tick or small interval
- Example: every 1–5 seconds real time

### Handles
- Ship movement
- Combat resolution
- Docking and undocking
- Resource transfer in progress
- Local sensor updates

### Scope
- Only **active entities**
- Player-owned assets
- Assets near players
- Ongoing battles or travel

Inactive regions are skipped.

---

## 2. Medium Tick (Operational Layer)

### Frequency
- Every X short ticks
- Example: every 5–15 minutes real time

### Handles
- Mining output accumulation
- Refinery production
- Trade route resolution
- Pirate growth and suppression
- Station upkeep and decay
- Local faction responses

### Scope
- Systems with:
  - Stations
  - Cities
  - Trade routes
- Recently active regions

Medium ticks are where the economy breathes.

---

## 3. Long Tick (Strategic Layer)

### Frequency
- Every many medium ticks
- Example: every 6–24 real-time hours

### Handles
- AI strategic decisions:
  - Declare war
  - Build stations
  - Construct ships
  - Launch expansion campaigns
  - Shift diplomatic stance
- Faction budget allocation
- Territory claims
- Large migration events

These decisions are **deliberate and rare**.

---

## AI Decision Model

### Why Long Ticks Matter
AI does not:
- React instantly
- Spam decisions
- Flip strategies constantly

Instead:
- AI evaluates state on long ticks
- Commits to plans
- Executes plans over many medium ticks

This creates believable empires.

---

## Event Scheduling

Some events are **scheduled** rather than tick-driven:

Examples:
- Station construction completion
- Ship build completion
- Research breakthroughs
- Political treaties expiring

Events trigger based on **game calendar dates**, not ticks.

---

## Regional Activation Model

To scale the universe:

- Regions are only fully simulated when:
  - Player assets are present
  - Trade routes pass through
  - Conflicts exist
- Dormant regions use **summary simulation**
- Summary sim updates:
  - Population
  - Economy
  - Stability
  - Pirate pressure

Details are resolved only when needed.

---

## Offline and Catch-Up Simulation

If the server lags or restarts:
- Game time advances using stored timestamps
- Missed medium/long ticks are resolved in batches
- Outcomes are deterministic

The universe never pauses.

---

## Player Perception of Time

Players experience time as:
- Calendar dates
- Construction timers
- Travel durations
- Economic cycles

They never see ticks.

This keeps immersion intact.

---

## Balance Implications
- Wars take weeks or months of game time
- Empires rise and fall over years
- Players can miss events and return to consequences
- No action is instantaneous at scale

---

## Version Notes
This model is designed to:
- Scale horizontally
- Support multiplayer persistence
- Allow future speed adjustments

If everything updates every tick, the design has failed.
Time layering is mandatory.
