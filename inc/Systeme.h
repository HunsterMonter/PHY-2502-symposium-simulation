#ifndef _SYSTEME_
#define _SYSTEME_

#include "Planete.h"
#include "utils.h"
#include <array>
#include <cmath>
#include <ranges>
#include <stdexcept>


template <size_t N>
class Systeme
{
public:
	template <typename... Planete>
	Systeme (const Planete&... ps) : planetes {ps...} {}


	template <size_t iter>
	std::array <std::array <Planete, N>, iter+1> simulation (long double epsillon)
	{
		std::array <std::array <Planete, N>, iter+1> output;
		output[0] = planetes;

		for (size_t i {0}; i < iter; i++)
		{
			step (1, epsillon);
			output[i+1] = planetes;
		}

		return output;
	}

private:
	void step (size_t T, long double epsillon)
	{
		const long double t {static_cast <long double> (86400 * T)};
		const size_t n_max {32};
		bool succes {false};

		const long double w0 {-std::cbrt (2) / (2 - std::cbrt (20))};
		const long double w1 {1 / (2 - std::cbrt (2))};

		const std::array <long double, 4> c {w1/2, (w0+w1)/2, (w0+w1)/2, w1/2};
		const std::array <long double, 4> d {w1, w0, w1, 0};

		std::array <Planete, N> state_old {planetes};

		for (size_t n {0}; n < n_max; n++)
		{
			std::array <Planete, N> state {planetes};

			const size_t nbPas {static_cast <size_t> (std::pow (2, n))};
			const long double deltaT {t / nbPas};

			for (size_t pas {0}; pas < nbPas; pas++)
			{
				for (size_t i {0}; i < c.size (); i++)
				{
					for (size_t j {0}; j < N; j++)
					{
						// Mettre à jour la position
						for (auto&& [xi, vi] : std::views::zip (state[j].pos, state[j].v))
						{
							xi += c[i] * vi * deltaT;
						}

						// Mettre à jour la vitesse
						// Itère sur les paires de planètes pour diviser en 2 le nombre de calculs à faire
						for (size_t k {0}; k < j; k++)
						{
							const std::array <long double, 3> p1 {state[j].pos};
							const std::array <long double, 3> p2 {state[k].pos};
							const long double mj {state[j].m};
							const long double mk {state[k].m};

							// Calcul de la force divisée par les deux masses entre la paire de planètes
							const std::array <long double, 3> delta {p1[0]-p2[0], p1[1]-p2[1], p1[2]-p2[2]};
							const long double r3 {std::pow (std::hypot (delta[0], delta[1], delta[2]), 3)};
							const long double force {-G*delta[0]/(2*r3), -G*delta[1]/(2*r3), -G*delta[2]/(2*r3)};

							for (auto&& [vj, vk, F] : std::views::zip (state[j].v, state[k].v, force))
							{
								vj += d[i] * mk * F * deltaT;
								vk -= d[i] * mj * F * deltaT;
							}
						}
					}
				}
			}

			// Compare state et state_old pour estimer l'erreur
			/*
			std::array <bool, 6*N> truth;

			for (size_t p {0}; p < N; p++)
			{
				const std::array <long double, 3> pos_old {state_old.pos};
				const std::array <long double, 3> pos {state.pos};

				const std::array <long double, 3> v_old {state_old.v};
				const std::array <long double, 3> v {state.v};

				for (size_t i {0}; i < 3; i++)
				{
					truth[p+i] = std::abs (pos[i] - pos_old[i]) / 15 < epsillon;
					truth[p+i+3] = std::abs (v[i] - v_old[i]) / 15 < epsillon;
				}
			}

			if (std::ranges::all_of (truth, [](bool b){ return b; }))
			{
				planetes = state;
				succes = true;
			}
			*/
			size_t truth {0};

			for (auto&& [p, p_old] : std::views::zip (state, state_old) | std::views::as_const)
			{
				for (auto&& [pos, pos_old] : std::views::zip (p.pos, p_old.pos) | std::views::as_const)
				{
					truth += std::abs (pos - pos_old) / 15 < epsillon;
				}

				for (auto&& [v, v_old] : std::views::zip (p.v, p_old.v) | std::views::as_const)
				{
					truth += std::abs (v - v_old) / 15 < epsillon;
				}
			}

			if (truth == 6*N)
			{
				planetes = state;
				succes = true;
			}
			else
			{
				state_old = state;
			}
		}

		if (!succes)
		{
			throw std::runtime_error ("La solution de l'évolution du système planétaire ne converge pas dans le temps alloué.");
		}
	}


	std::array <Planete, N> planetes;
};

#endif
