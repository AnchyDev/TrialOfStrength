#ifndef MODULE_TRIAL_OF_STRENGTH_INSTANCE_SCRIPT_H
#define MODULE_TRIAL_OF_STRENGTH_INSTANCE_SCRIPT_H

#include "ScriptMgr.h"

#include "TrialOfStrength.h"
#include "ToSMapMgr.h"

class ToSInstanceScript : public InstanceScript
{
public:
    ToSInstanceScript(Map* map) : InstanceScript(map)
    {
        arenaMaster = nullptr;
        arenaMasterLeft = false;

        rewardChest = nullptr;
        rewardBeam = nullptr;

        combatantPosStart = new Position(228.324, -99.921, 18.007, 6.282);
        combatantPosEnd = new Position(265.175, -100.163, 18.677, 3.121);

        ResetEncounter();
    }
    void OnCreatureCreate(Creature* creature) override;

    bool IsSubWaveCleared() const;
    bool IsWaveCleared() const;
    bool HasMoreWaves() const;
    bool IsWaveInProgress() const;

    void SpawnNextWave(ToSWaveTemplate* /*waveTemplate = nullptr*/);

    void MakeEntrance(Creature* creature);
    void SetCombatantsHostile();
    uint32 GetRemainingAlive() const;

    void AddCurse(uint32 curseId);
    void ApplyCurses(Unit* unit);
    void ApplyCursesToPlayers();
    void ClearCurses(Unit* unit);
    void ClearCursesFromPlayers();

    void Update(uint32 diff) override;

    void CheckArenaMasterRelocate();
    void RelocateArenaMaster(bool returning);

    bool AnyPlayerAlive();

    bool CheckFailure();

    void NotifyFailure();
    void NotifyPlayers();

    void SetupEncounter();

    void CheckWaveCompletion();
    void PopulateRewardChest();
    void AnnounceCompletion();

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

    bool waveCleared;
    bool trialCompleted;
    bool cheerPlayed;

    std::vector<Creature*> waveCreatures;
    std::vector<ToSCurseTemplate*> curses;

    Creature* arenaMaster;
    bool arenaMasterLeft;

    Position* combatantPosStart;
    Position* combatantPosEnd;

    GameObject* rewardChest;
    GameObject* rewardBeam;
};

#endif // MODULE_TRIAL_OF_STRENGTH_INSTANCE_SCRIPT_H
