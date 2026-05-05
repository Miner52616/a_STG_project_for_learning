phasetable=
{   
    {
        type="MidPhase",
        time=360,
        enemytable=
        {
            {
                x=460,
                y=100,
                HP=50,
                start=60,
                End=216000,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },
                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=25
                        }
                    },
                    
                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=10
                        }
                    },
                }
            },

            {
                x=410,
                y=100,
                HP=50,
                start=60,
                End=216000,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },
                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=25
                        }
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=10
                        }
                    },
                }
            },

            {
                x=360,
                y=100,
                HP=50,
                start=60,
                End=216000,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },
                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=25
                        }
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=10
                        }
                    },
                }
            },

            {
                x=310,
                y=100,
                HP=50,
                start=60,
                End=216000,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },
                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=25
                        }
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=10
                        }
                    },
                }
            },
        }
    },

    {
        type="BossPhase",
        spelltable=
        {
            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=3,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                spellcard=false,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=250
                    }
                }
            },

            {
                time=2400,
                HP=3600,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=2,
                name_x=-100,
                name_y=-100,
                voidspell=false,
                spellcard=true,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="NewNonSpell1"
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=10
                        }
                    },
                }
            },

            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=2,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                spellcard=false,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=300
                    }
                }
            },

            {
                time=4200,
                HP=3600,
                bossname="Kochiya Sanae",
                spellname="「骤然风雨」",
                spellnum=3,
                name_x=750,
                name_y=25,
                voidspell=false,
                spellcard=true,
                behaviortable=
                {
                    {
                        type="SuddenRain"
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=20
                        }
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=5
                        }
                    },
                }
            },

            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=2,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                spellcard=false,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=250
                    }
                }
            },

            {
                time=4200,
                HP=4200,
                bossname="Kochiya Sanae",
                spellname="岚符「大孔雀暴风」",
                spellnum=2,
                name_x=750,
                name_y=25,
                voidspell=false,
                spellcard=true,
                behaviortable=
                {
                    {
                        type="TheStorm"
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=20
                        }
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=5
                        }
                    },
                }
            },

            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=1,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                spellcard=false,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=350
                    }
                }
            },

            {
                time=2400,
                HP=4500,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=1,
                name_x=-100,
                name_y=-100,
                voidspell=false,
                spellcard=true,
                behaviortable=
                {
                    {
                        type="NonSpell2"
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=10
                        }
                    },
                }
            },

            {
                time=120,
                HP=3000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=1,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                spellcard=false,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=250
                    }
                }
            },

            {
                time=4200,
                HP=3600,
                bossname="Kochiya Sanae",
                spellname="「呼唤流星的星术仪式」",
                spellnum=1,
                name_x=750,
                name_y=25,
                voidspell=false,
                spellcard=true,
                behaviortable=
                {
                    {
                        type="StarRite"
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=20
                        }
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=5
                        }
                    },
                }
            },

            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=2,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                spellcard=false,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=300
                    }
                }
            },

            {
                time=1800,
                HP=3000,
                bossname="Kochiya Sanae",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
                name_y=25,
                voidspell=false,
                spellcard=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="BreezyBlossom1"
                    }
                }
            },

            {
                time=1800,
                HP=3500,
                bossname="Kochiya Sanae",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
                name_y=25,
                voidspell=false,
                spellcard=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    }
                }
            },

            {
                time=1800,
                HP=3500,
                bossname="Kochiya Sanae",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
                name_y=25,
                voidspell=false,
                spellcard=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    },

                    {
                        type="BreezyBlossom3"
                    }
                }
            },

            {
                time=1800,
                HP=3000,
                bossname="Kochiya Sanae",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
                name_y=25,
                voidspell=false,
                spellcard=true,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    },

                    {
                        type="BreezyBlossom3"
                    },

                    {
                        type="BreezyBlossom4"
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Score",
                            dropnum=25
                        }
                    },

                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=5
                        }
                    },
                }
            }
        }
    },
}

store=
{
    {
        type="BossPhase",
        spelltable=
        {
            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=3,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=250
                    }
                }
            },

            {
                time=1800,
                HP=3000,
                bossname="Kochiya Sanae",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    },

                    {
                        type="BreezyBlossom3"
                    },

                    {
                        type="BreezyBlossom4"
                    }
                }
            },

            {
                time=4200,
                HP=3600,
                bossname="Kochiya Sanae",
                spellname="「骤然风雨」",
                spellnum=2,
                name_x=750,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="SuddenRain"
                    }
                }
            },

            {
                time=4200,
                HP=3600,
                bossname="Kochiya Sanae",
                spellname="「呼唤流星的星术仪式」",
                spellnum=3,
                name_x=750,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="StarRite"
                    }
                }
            },

            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=2,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=300
                    }
                }
            },

            

            {
                time=2400,
                HP=3600,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=1,
                name_x=-100,
                name_y=-100,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="NewNonSpell1"
                    }
                }
            },

            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=1,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=300
                    }
                }
            },

            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=1,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=250
                    }
                }
            },

            {
                time=4200,
                HP=3600,
                bossname="Kochiya Sanae",
                spellname="岚符「大孔雀暴风」",
                spellnum=1,
                name_x=750,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="TheStorm"
                    }
                }
            },

            {
                time=120,
                HP=2000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=0,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=350
                    }
                }
            },

            {
                time=2400,
                HP=3600,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=0,
                name_x=-100,
                name_y=-100,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="NonSpell2"
                    }
                }
            },

            {
                time=120,
                HP=3000,
                bossname="Kochiya Sanae",
                spellname=" ",
                spellnum=0,
                name_x=-100,
                name_y=-100,
                voidspell=true,
                behaviortable=
                {
                    {
                        type="MoveTo",
                        v=0.1,
                        x=385,
                        y=250
                    }
                }
            },

            {
                time=1800,
                HP=3000,
                bossname="Kochiya Sanae",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="BreezyBlossom1"
                    }
                }
            },

            {
                time=1800,
                HP=3500,
                bossname="Kochiya Sanae",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    }
                }
            },

            {
                time=1800,
                HP=3500,
                bossname="Kochiya Sanae",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    },

                    {
                        type="BreezyBlossom3"
                    }
                }
            },

            {
                time=1800,
                HP=3000,
                bossname="Kochiya Sanae",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    },

                    {
                        type="BreezyBlossom3"
                    },

                    {
                        type="BreezyBlossom4"
                    }
                }
            }
        }
    },

    {
        type="MidPhase",
        time=360,
        enemytable=
        {
            {
                x=460,
                y=100,
                HP=200,
                start=60,
                End=216000,
                behaviortable=
                {
                    {
                        type="MoveToRandom1",
                        start_time=30,
                    },
                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=80
                        }
                    },
                }
            }
        }
    },
}