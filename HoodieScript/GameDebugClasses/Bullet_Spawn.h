#pragma once

namespace hoodie_script {
    enum class bullet_type : unsigned int {
        Firebomb = 110,
        BlackFirebomb = 115,
        AlluringSkull = 120,
        PrismStone = 130,
        DungPie = 150,
        UndeadHunterCharm = 160,
        LightningUrn = 250,
        DuelCharm = 270,
        ThrowingKnife = 300,
        PoisonThrowingKnife = 301,
        LaceratingThrowingKnife = 302,
        ChurchGuardianShiv = 305,
        RopeFirebomb = 320,
        RopeBlackFirebomb = 330,
        StalkDungPie = 340,
        DragonslayerGreatarrow = 700,
        ChaosBedVestiges = 12456000,
        FloatingChaosOrb = 12457000,
        SeethingChaos = 12660000,
        StationaryFireball = 135050,
        WtfDeepsoul = 5222800,

        Arrow = 500,
        LargeArrow = 510,

        FarronDart = 11210000,
        SoulArrow = 11300000,
        SoulStream = 11620000,
        ChaosStorm = 12451000,
        ProfanedFlame = 12455000,
        PoisonMist = 12420000,
        ToxicMist = 12421000,
        Force = 13530000,
        WrathOfTheGods = 13531000,
        EmitForce = 13532000,
        AcidSurge = 12422000,
        DivinePillarsOfLight = 13720000,
        SunlightSpear = 13552000,

        SmoulderingLakeTurretArrow = 2260700,

        AldrichPurpleExplosion = 5150740,
        CrescentBlade = 100041000,
        StanceOfJudgement = 100061700,
        HurlSpear = 100092300,
        SpellParry = 100202800,
        WayOfWhiteCorona = 13556000,
        WayOfWhiteCoronaStationary = 13556010,

        BlueSentinelOrb = 1000,
        PlayerTrackerRed = 1001,
        PlayerTrackerGrey = 1002,
        PlayerTrackerGreen = 1003,

        // Shit to use when fucking with friends
        BurgerFlip = 12403300,

        // Carvings
        HelloCarving = 400,
        HelloCarvingImpact = 401,
        ThankYouCarving = 405,
        ThankYouCarvingImpact = 406,
        VeryGoodYouCarving = 410,
        VeryGoodYouCarvingImpact = 411,
        ImSorryCarving = 415,
        ImSorryCarvingImpact = 416,
        HelpMeCarving = 420,
        HelpMeCarvingImpact = 421,
    };


    class bullet_spawn_request {
    public:
        void set_owner(int32_t ownerHandle);
        int32_t get_owner();

        void set_bullet_param_id(bullet_type bulletType);
        bullet_type get_bullet_param_id();

        void set_network_flag(int32_t networkFlag);
        int32_t get_network_flag();

        void set_turret_flag(int32_t turretFlag);
        int32_t get_turret_flag();

        void set_homing_flag(int32_t homingFlag);
        int32_t get_homing_flag();

        void set_coordinates(std::vector<float> coordinates);
        std::vector<float> get_coordinates();

        void set_direction(std::vector<float> direction);
        std::vector<float> get_direction();

    private:
        int32_t _owner = -1;
        int32_t _bulletParamId = -1;
        int32_t _turretFlag = 0;
        int32_t _homingFlag = -1;
        int32_t _networkFlag = 9;
        std::vector<float> _coordinates;
        std::vector<float> _direction;
    };

    class bullet_facade {
    public:
        static void spawn(bullet_spawn_request* request);
    };
}