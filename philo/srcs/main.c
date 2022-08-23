#include "../includes/philosophers.h"

int	main (int argc, char **argv)
{
	info_t	info;
	int		key;

	key = ft_check_args(argc, argv, &info.ph_const);
	if (key)	
		return (ft_printer_error(key), 1);
	key = ft_init_info(&info, info.ph_const.nb_ph);
	if (key)
		return (ft_printer_error(key), 1);
	key = ft_init_threads(info.all_threads, info.philos, info.ph_const.nb_ph);
	if (key)
		return (ft_printer_thread_error(&info, key));
	while (timestamp(info.begin) < 30)
		usleep(300);
	info.begin += 30;
	while (ft_check_end(&info))
		ft_dead_checker(&info, info.ph_const.time_to_die,
			info.ph_const.nb_ph);
	key = ft_waiting_threads(&info);
	if (key)
		return (ft_free_table(&info), ft_printer_error(key), 1);
	ft_free_table(&info);
	return (0);
}
