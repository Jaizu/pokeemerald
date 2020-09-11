Common_EventScript_SetGymTrainers::
	switch VAR_0x8008
	case 1, SerosVillage_Gym_SetGymTrainers
	case 2, NestpineTown_Gym_SetGymTrainers
	end

SerosVillage_Gym_SetGymTrainers::
	settrainerflag TRAINER_ROSE
	settrainerflag TRAINER_COURTNEY
	settrainerflag TRAINER_DAZ
	settrainerflag TRAINER_HANA
	return

NestpineTown_Gym_SetGymTrainers:
	settrainerflag TRAINER_WILHELM
	settrainerflag TRAINER_GORDON
	settrainerflag TRAINER_PETER
	settrainerflag TRAINER_JANE
	settrainerflag TRAINER_CEDRIC
	return
