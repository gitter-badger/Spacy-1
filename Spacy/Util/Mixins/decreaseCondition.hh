#ifndef ALGORITHM_UTIL_MIXIN_DECREASE_CONDITION_HH
#define ALGORITHM_UTIL_MIXIN_DECREASE_CONDITION_HH

namespace Spacy
{
  namespace Mixin
  {
    /**
     * @ingroup MixinGroup
     * @brief %Mixin class for accepting local models \f$m\f$ of nonlinear optimization problems \f$\min f(x)\f$.
     *
     *
     */
    class DecreaseCondition
    {
    public:
      /**
       * @brief Constructor.
       * @param minimalDecrease minimal required decrease
       * @param relaxedMinimalDecrease relaxed required decrease
       */
      explicit DecreaseCondition(double minimalDecrease = 0.5, double relaxedMinimalDecrease = 0.1) noexcept;

      /**
       * @brief Set required minimal decrease.
       * @param decrease minimal required decrease
       */
      void setMinimalDecrease(double decrease) noexcept;

      /**
       * @brief Access minimal decrease.
       * @return minimal decrease
       */
      double minimalDecrease() const noexcept;

      /**
       * @brief Set relaxed minimal decrease.
       * @param decrease relaxed required decrease
       *
       * This is used for deciding about rejecting tangential steps in CompositeSteps::AffineCovariantSolver.
       */
      void setRelaxedMinimalDecrease(double decrease) noexcept;

      /**
       * @brief Decide if measure relative decrease is acceptable.
       * @param decrease measured relative decrease \f$\delta m/\delta f\f$.
       */
      bool acceptableDecrease(double decrease) const noexcept;

      /**
       * @brief Decide if measure relative decrease is acceptable with respect to the relaxed decrease condition.
       * @param decrease measured relative decrease \f$\delta m/\delta f\f$.
       */
      bool acceptableRelaxedDecrease(double decrease) const noexcept;

    private:
      double minimalDecrease_, relaxedMinimalDecrease_;
    };
  }
}

#endif // ALGORITHM_UTIL_MIXIN_DECREASE_CONDITION_HH