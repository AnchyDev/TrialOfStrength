![banner](https://cdn.discordapp.com/attachments/740999436876120127/1168057693907460136/banner2.png?ex=6550617f&is=653dec7f&hm=94411fcc08408464d7c1276c97f7246c965550efa86291ccef073e796d8691f6&)
Trial of Strength (ToS) is an AzerothCore module that adds a test of strength arena to test players skills in combat.

## Features
- Waves of monsters to fight.
- Rewards at the end of every wave.
- Curses to add difficulty and increase rewards.
- Supports group play.

[![Preview Video](https://img.youtube.com/vi/ZE_VsCWJNCw/0.jpg)](https://youtu.be/ZE_VsCWJNCw)

## Setup
1. Clone the module into your AzerothCore modules directory.
2. Setup the `creature_template` table with creatures you would like to use in the arena.
3. Pick one of the [CombatAI types](https://gist.github.com/AnchyDev/7d8847fd696e42c94efcfdc5baf88e7f) for each of the creatures you create.
4. Setup the `tos_wave_groups` table with your created creatures.
5. Setup the `tos_reward_template` with your rewards for each wave.
6. Create wave entries in `tos_wave_template` which links to your `tos_wave_groups` and `tos_reward_template` entries.
7. Enable the module.
8. Spawn the arena entry (entry: 441250) NPC anywhere you want.

## Note
This module is a work in progress, so expect bugs and crashes as the module is not heavily tested.

## Contact
If you have any issues setting up the module, you can [contact me on my community Discord](https://discord.gg/xdVPGcpJ8C).
