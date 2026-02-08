# Event System Overview

This document defines how **important happenings in the universe** are detected, recorded,
and presented to players. Events are how the simulation becomes *visible* and *narrative*
without scripted stories.

The event system does not drive the universe — it **reports and reacts to it**.

---

## Core Design Philosophy
- The universe runs independently of the player
- Events surface consequences, not causes
- No scripted campaigns or forced story arcs
- Information is imperfect and faction-dependent
- Events create memory, history, and tension

Events are how players *understand* a living universe.

---

## What Is an Event?

An event is a **notable state change** in the simulation that:
- Alters the strategic landscape
- Affects factions, trade, or stability
- Is worth communicating to players

Examples:
- War declarations
- System blockades
- Capital ship destruction
- Faction collapse or fragmentation
- Major trade route disruption
- Discovery of rare resources
- Player actions with wide impact

---

## Event Categories

### 1. Political Events
- War declared
- Ceasefire or peace treaty
- Alliance formed or broken
- Sanctions imposed
- Faction schism

**Impact**
- Reputation shifts
- Trade restrictions
- Military posturing
- News escalation

---

### 2. Military Events
- Capital ship destroyed
- Major fleet engagement
- System invaded
- Gate seized or heavily interdicted

**Impact**
- Power balance shifts
- Security changes
- Piracy spikes
- Strategic reevaluation

---

### 3. Economic Events
- Trade corridor collapse
- Market crash
- Resource shortage
- New trade hub emerges

**Impact**
- Price volatility
- Migration of trade routes
- Smuggling growth
- Contract changes

---

### 4. Industrial Events
- Major station constructed or destroyed
- Shipyard activated
- Capital production begun
- Industrial sabotage

**Impact**
- Tech access changes
- Production capacity shifts
- Political attention increases

---

### 5. Security & Piracy Events
- Pirate warlord rises
- Pirate stronghold destroyed
- Region destabilizes
- Smuggling ring exposed

**Impact**
- Patrol requirements
- Insurance costs
- Contract availability

---

### 6. Exploration & Discovery Events
- Rare resource discovered
- Ancient ruin found
- Anomaly detected
- New gate route charted

**Impact**
- Strategic interest
- Faction competition
- Player opportunity

---

## Event Generation

### Automatic Detection
Events are generated when simulation thresholds are crossed.

Examples:
- Fleet losses exceed X%
- Trade volume drops below threshold
- System stability falls rapidly
- Capital ship build queue starts

No manual scripting required.

---

### Scheduled Events
Some events are scheduled based on:
- Construction completion
- Treaties expiring
- Research capability unlocks

These use the **game calendar**, not ticks.

---

## Information Visibility

Not all factions learn about events equally.

### Information Factors
- Distance
- Sensor coverage
- Intelligence networks
- Faction doctrine (e.g., Noctyr advantage)
- Player assets nearby

This enables:
- Rumors
- Delayed news
- False reports

---

## Player-Facing Presentation

### Galactic News Network (GNN)
Major events appear as:
- Headlines
- Breaking news
- Historical summaries

Tone varies by faction and region.

---

### Regional Alerts
Localized notifications for:
- Player-owned assets
- Nearby conflicts
- Trade disruptions

---

### Personal Logs
Player-specific records of:
- Asset losses
- Reputation changes
- Completed milestones

---

## Event Severity Levels

| Severity | Example | Visibility |
|--------|--------|------------|
| Minor | Pirate raid | Local |
| Moderate | Trade route disrupted | Regional |
| Major | Capital ship destroyed | Galactic |
| Historic | Faction collapse | Permanent record |

Severity controls:
- Notification style
- Persistence
- AI reaction weight

---

## AI Reaction to Events

Events feed back into AI:

- Strategic AI reassesses goals
- Operational AI reallocates assets
- Minor factions seek protection
- Pirates exploit chaos

Events are **inputs**, not just outputs.

---

## Persistence and History

### Event Archive
All major events are stored:
- With date/time
- Involved factions
- Systems affected
- Outcome summary

The galaxy has a **memory**.

---

### Historical Weight
Past events influence:
- Diplomatic trust
- Fear and deterrence
- AI risk tolerance

History matters.

---

## Player-Created Events

Player actions can generate events:
- First station built
- First capital ship launched
- First system controlled
- Trade hub established
- Faction collapse caused

These are highlighted specially.

---

## Performance Considerations

- Event detection is cheap (threshold-based)
- Event propagation is filtered by relevance
- Dormant regions generate fewer events
- Old minor events are summarized, not replayed

---

## Version Notes

If events:
- Feel spammy → thresholds are too low
- Feel silent → thresholds are too high
- Feel scripted → detection logic is wrong

Events should feel **inevitable, not authored**.
