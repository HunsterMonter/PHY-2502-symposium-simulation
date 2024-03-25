#ifndef _SYSTEME_
#define _SYSTEME_

#include "Planete.h"
#include "arrayOps.h"
#include "utils.h"
#include <array>
#include <cmath>
#include <concepts>
#include <ranges>
#include <stdexcept>
#include <iostream>


template <std::floating_point T, size_t dim, size_t N>
class Systeme
{
public:
	template <typename... Planete>
	Systeme (const Planete&... ps) : planetes {ps...} {}


	template <size_t iter>
	std::array <std::array <Planete <T, dim>, N>, iter+1> simulation (T epsillon)
	{
		std::array <std::array <Planete <T, dim>, N>, iter+1> output;
		output[0] = planetes;

		for (size_t i {0}; i < iter; i++)
		{
			step (1, epsillon);
			output[i+1] = planetes;
		}

		return output;
	}

private:
	void step (size_t jours, T epsillon)
	{
		const T temps {static_cast <T> (86400 * jours)};
		const size_t n_max {32};
		bool succes {false};

		const T w0 {-std::cbrt (2) / (2 - std::cbrt (2))};
		const T w1 {1 / (2 - std::cbrt (2))};

		const std::array <T, 4> c {w1/2, (w0+w1)/2, (w0+w1)/2, w1/2};
		const std::array <T, 4> d {w1, w0, w1, 0};

		std::array <Planete <T, dim>, N> state_old {planetes};

		for (size_t n {0}; n < n_max; n++)
		{
			std::array <Planete <T, dim>, N> state {planetes};

			const size_t nbPas {static_cast <size_t> (std::pow (2, n))};
			const T deltaT {temps / nbPas};

			for (size_t pas {0}; pas < nbPas; pas++)
			{
				for (size_t i {0}; i < c.size (); i++)
				{
					for (size_t j {0}; j < N; j++)
					{
						// Mettre à jour la position
						//std::cout << state[j].pos[0] << " ";
						state[j].pos += c[i] * state[j].v * deltaT;
						//std::cout << state[j].pos[0] << std::endl;

						// Mettre à jour la vitesse
						// Itère sur les paires de planètes pour diviser en 2 le nombre de calculs à faire
						for (size_t k {0}; k < j; k++)
						{
							const std::array <T, dim> F {force (state[j].pos, state[k].pos)};
							//std::cout << F[0] << " " << F[1] << std::endl;

							state[j].v += d[i] * state[k].m * F * deltaT;
							state[k].v -= d[i] * state[j].m * F * deltaT;
						}
					}
				}
			}

			// Compare state et state_old pour estimer l'erreur
			/*
			std::array <bool, 6*N> truth;

			for (size_t p {0}; p < N; p++)
			{
				const std::array <T, 3> pos_old {state_old.pos};
				const std::array <T, 3> pos {state.pos};

				const std::array <T, 3> v_old {state_old.v};
				const std::array <T, 3> v {state.v};

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
			std::cout << "Nombre de pas: " << nbPas << std::endl;
			size_t truth {0};

			for (auto&& [p, p_old, planete] : std::views::zip (state, state_old, planetes) | std::views::as_const)
			{
				for (auto&& [deltaPos, deltaPos_old] : std::views::zip (p.pos-planete.pos, p_old.pos-planete.pos) | std::views::as_const)
				{
					truth += std::abs (deltaPos - deltaPos_old) / 15 < max_err (deltaPos, deltaPos_old, epsillon);
					//std::cout << std::abs (deltaPos - deltaPos_old) / 15 << " " << max_err (deltaPos, deltaPos_old, epsillon) << "\n";
					//std::cout << deltaPos << " " << deltaPos_old << std::endl;
				}

				for (auto&& [deltaV, deltaV_old] : std::views::zip (p.v-planete.v, p_old.v-planete.v) | std::views::as_const)
				{
					truth += std::abs (deltaV - deltaV_old) / 15 < max_err (deltaV, deltaV_old, epsillon);
					//std::cout << std::abs (deltaV - deltaV_old) / 15 << " " << max_err (deltaV, deltaV_old, epsillon) << "\n";
				}
			}

			if (truth == 2*dim*N)
			{
				planetes = state;
				succes = true;
				break;
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


	std::array <Planete <T, dim>, N> planetes;
};

#endif
