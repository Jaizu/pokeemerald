Common_EventScript_SetGymTrainers::
	switch VAR_0x8008
	case 0, SerosVillage_Gym_SetGymTrainers
	case 1, NestpineTown_Gym_SetGymTrainers
	case 2, WindmistCity_Gym_SetGymTrainers
	case 3, ValoonTown_Gym_SetGymTrainers
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

WindmistCity_Gym_SetGymTrainers:
	settrainerflag TRAINER_HECTOR
	settrainerflag TRAINER_ANGELICA
	settrainerflag TRAINER_JUNIOR
	return

ValoonTown_Gym_SetGymTrainers:
	settrainerflag TRAINER_JAMES
	settrainerflag TRAINER_CLAUDE
	settrainerflag TRAINER_KENT
	settrainerflag TRAINER_RUBY
	settrainerflag TRAINER_KEIGO
	settrainerflag TRAINER_CALE
	return
