#ifndef MODULE_TRIAL_OF_STRENGTH_INSTANCE_SCRIPT_H
#define MODULE_TRIAL_OF_STRENGTH_INSTANCE_SCRIPT_H

#include "ScriptMgr.h"

#include "TrialOfStrength.h"
#include "ToSMapMgr.h"

class ToSInstanceScript : public InstanceScript
{
private:
    enum ToSInstanceConstants
    {
        TOS_SOUND_HORN = 6140,
        TOS_SOUND_CHEER = 13904,
        TOS_SOUND_FAIL = 847,

        TOS_GOB_REWARD_CHEST = 441250,
        TOS_GOB_REWARD_BEAM = 441251,
        TOS_GOB_CURSE = 441252,

        TOS_SPELL_EXHAUSTION = 57723
    };
public:
    ToSInstanceScript(Map* map) : InstanceScript(map)
    {
        arenaMaster = nullptr;
        arenaMasterLeft = false;

        rewardChest = nullptr;
        rewardBeam = nullptr;

        curseCrystal1 = nullptr;
        curseCrystal2 = nullptr;
        curseCrystal3 = nullptr;

        combatantPosStart = new Position(228.324, -99.921, 18.007, 6.282);
        combatantPosEnd = new Position(249.918, -100.063, 18.679, 0.030);

        ResetEncounter();
    }
    void OnCreatureCreate(Creature* creature) override;

    bool IsSubWaveCleared() const;
    bool IsWaveCleared() const;
    bool HasMoreWaves() const;
    bool IsWaveInProgress() const;

    void SpawnNextWave(ToSWaveTemplate* /*waveTemplate = nullptr*/);

    void MakeEntrance(Creature* creature, float diff);
    void SetCombatantsHostile();
    uint32 GetRemainingAlive() const;

    void AddCurse(uint32 curseId);
    void ApplyCurses(Unit* unit);
    void ApplyCursesToPlayers();
    void ApplyAutoScaling(Creature* creature);
    void ClearCursesFromPlayers();
    void SpawnCurseCrystals();
    void DespawnCurseCrystals();
    uint32 GetCurseForGUID(ObjectGuid guid);
    uint32 GetCurseScaling();
    void ReloadCurses();
    uint32 GetRandomAvailableCurse();
    std::vector<uint32> GetRandomAvailableCurses(uint32 count);
    void RemoveAvailableCurse(uint32 curseId);

    void Update(uint32 diff) override;

    void CheckArenaMasterRelocate();
    void RelocateArenaMaster(bool returning);
    void TryTeleportPlayers();

    bool AnyPlayerAlive();
    bool AnyPlayerInArena(bool checkAlive = false);

    bool CheckFailure();

    void NotifyFailure();
    void ResetPlayerCooldowns();
    void NotifyPlayers();

    void SetupEncounter();

    void CheckWaveCompletion();
    void PopulateRewardChest();
    bool IsRewardChestEmpty();
    void AnnounceCompletion();
    void SendInvadersWorldState(bool state, uint32 invaders = 0);
    void UpdateInvadersWorldState(uint32 invaders);
    uint32 GetCurrentWaveTotal();

    void PlayCrowd();

    void SetData(uint32 dataId, uint32 value) override;
    uint32 GetData(uint32 dataId) const override;

    bool IsEncounterInProgress() const override;

    void CleanupCreatures();
    void CleanupGameObjects();
    void ResetEncounter();

private:
    EventMap events;

    bool encounterInProgress;
    bool waveInProgress;

    uint32 currentWave;
    uint32 totalWaves;
    uint32 currentSubGroup;
    uint32 totalSubGroups;
    uint32 totalInvaders;

    bool waveCleared;
    bool trialCompleted;
    bool cheerPlayed;

    std::vector<Creature*> waveCreatures;
    std::vector<ToSCurseTemplate*> curses;
    std::vector<uint32> availableCurseIds;

    Creature* arenaMaster;
    bool arenaMasterLeft;

    Position* combatantPosStart;
    Position* combatantPosEnd;

    GameObject* rewardChest;
    GameObject* rewardBeam;

    GameObject* curseCrystal1;
    uint32 curseId1;
    GameObject* curseCrystal2;
    uint32 curseId2;
    GameObject* curseCrystal3;
    uint32 curseId3;
};

#endif // MODULE_TRIAL_OF_STRENGTH_INSTANCE_SCRIPT_H
